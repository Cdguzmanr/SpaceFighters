
#include "Level.h"
#include "EnemyShip.h"
#include "Blaster.h"
#include "PowerUp.h"

class PlayerShip;
// Collision Callback Functions
void PlayerShootsEnemy(GameObject* pObject1, GameObject* pObject2)
{

	bool m = pObject1->HasMask(CollisionType::ENEMY);
	EnemyShip* pEnemyShip = (EnemyShip*)((m) ? pObject1 : pObject2);
	Projectile* pPlayerProjectile = (Projectile*)((!m) ? pObject1 : pObject2);
	KillsCounter* pKillsCounter = (KillsCounter*)((!m) ? pObject1 : pObject2);

	pEnemyShip->Hit(pPlayerProjectile->GetDamage());
	if (!pEnemyShip->IsActive())
	{


		// Generate random power-up
		int randomNum = Math::GetRandomInt(1, 10);
		if (randomNum <= 10) // 30% chance of power-up
			//push comment

		{
			PowerUp* pPowerUp = pEnemyShip->GetCurrentLevel()->GetPowerUp();
			if (pPowerUp)
				pPowerUp->Initialize(pEnemyShip->GetPosition(), 0.1);
		}
	    
		pKillsCounter->AddKill(1); // add to the kill counter score

		

	}


	pPlayerProjectile->Deactivate(); 
}

void PlayerCollidesWithEnemy(GameObject* pObject1, GameObject* pObject2)
{
	bool m = pObject1->HasMask(CollisionType::PLAYER);
	PlayerShip* pPlayerShip = (PlayerShip*)((m) ? pObject1 : pObject2);
	EnemyShip* pEnemyShip = (EnemyShip*)((!m) ? pObject1 : pObject2);
	pPlayerShip->Hit(std::numeric_limits<float>::max());
	pEnemyShip->Hit(std::numeric_limits<float>::max());
}

void PlayerCollidesWithPowerUp(GameObject* pObject1, GameObject* pObject2)
{
	bool m = pObject1->HasMask(CollisionType::PLAYER);

	// Calls Objects to set sprites
	PlayerShip* pPlayerShip = (PlayerShip*)((m) ? pObject1 : pObject2);
	Projectile* pProjectile = (Projectile*)((m) ? pObject1 : pObject2);
	PowerUp* pPowerUp = (PowerUp*)((!m) ? pObject1 : pObject2);


	// TODO: Effect on PlayerShip

		// 1- Change Ship and bullet Textures
	if (pPlayerShip->IsActive())
	{

		pPlayerShip->SetTexture(pPlayerShip->GetCurrentLevel()->GetPowerUpShipTexture());
		pProjectile->SetTexture(pProjectile->GetCurrentLevel()->GetPowerUpBulletTexture());


		// 2- Choose random power up
		/*
		pPowerUp->SetType(PowerUp:: "enum random value" );
		*/


		// Testing - RapidFire PowerUP
		pPowerUp->SetType(PowerUp::RapidFire);


		// 3- Make PowerUp effect
		pPowerUp->ActivatePowerUp();

		// Activate Power up
		Blaster* pBlaster = dynamic_cast<Blaster*>(pPlayerShip->GetWeapon(0));
		if (pBlaster) pBlaster->SetCooldownBoost(pPowerUp->GetRapidFireRate());
	}

	pPowerUp->Deactivate();

}



Level::Level()
{
	m_sectorSize.X = 64;
	m_sectorSize.Y = 64;

	m_sectorCount.X = (Game::GetScreenWidth() / (int)m_sectorSize.X) + 1;
	m_sectorCount.Y = (Game::GetScreenHeight() / (int)m_sectorSize.Y) + 1;

	m_totalSectorCount = m_sectorCount.X * m_sectorCount.Y;

	m_pSectors = new std::vector<GameObject*>[m_totalSectorCount];
	m_pCollisionManager = new CollisionManager();

	GameObject::SetCurrentLevel(this);

	// Setup player ship
	m_pPlayerShip = new PlayerShip();
	Blaster* pBlaster = new Blaster(true);
	pBlaster->SetProjectilePool(&m_projectiles);
	m_pPlayerShip->AttachWeapon(pBlaster, Vector2::UNIT_Y * -20);

	for (int i = 0; i < 100; i++)
	{
		Projectile* pProjectile = new Projectile();
		m_projectiles.push_back(pProjectile);
		AddGameObject(pProjectile);
	}


	m_pPlayerShip->Activate();
	AddGameObject(m_pPlayerShip);

	// Setup collision types
	CollisionManager* pC = GetCollisionManager();

	CollisionType playerShip = (CollisionType::PLAYER | CollisionType::SHIP);
	CollisionType playerProjectile = (CollisionType::PLAYER | CollisionType::PROJECTILE);
	CollisionType enemyShip = (CollisionType::ENEMY | CollisionType::SHIP);
	CollisionType powerUp = (CollisionType::POWERUP | CollisionType::PLAYER);

	pC->AddNonCollisionType(playerShip, playerProjectile);
	pC->AddCollisionType(playerProjectile, enemyShip, PlayerShootsEnemy);
	pC->AddCollisionType(playerShip, enemyShip, PlayerCollidesWithEnemy);
	pC->AddCollisionType(playerShip, powerUp, PlayerCollidesWithPowerUp);

	m_pKillsCounter = new KillsCounter();
}

Level::~Level()
{
	delete[] m_pSectors;
	delete m_pCollisionManager;

	delete m_pKillsCounter;

	m_gameObjectIt = m_gameObjects.begin();
	for (; m_gameObjectIt != m_gameObjects.end(); m_gameObjectIt++)
	{
		delete (*m_gameObjectIt);
	}
}


void Level::LoadContent(ResourceManager* pResourceManager)
{
	m_pPlayerShip->LoadContent(pResourceManager);

	// Load background texture
	m_pTexture = pResourceManager->Load<Texture>("Textures\\backspace.png");
	m_texturePosition = Game::GetScreenCenter();



	// Load textures for Power ups
	m_pPowerUpTexture = pResourceManager->Load<Texture>("Textures\\PowerUpF.png");
	m_pPowerUpBulletTexture = pResourceManager->Load<Texture>("Textures\\BulletRed.png");
	m_pPowerUpShipTexture = pResourceManager->Load<Texture>("Textures\\PlayerShipRed.png");

	for (int i = 0; i < 4; i++)
	{
		PowerUp* pPowerUp = new PowerUp();
		pPowerUp->SetTexture(GetPowerUpTexture());

		m_PowerUps.push_back(pPowerUp);
		AddGameObject(pPowerUp);
	}

	m_pKillsCounter->LoadContent(pResourceManager);

}


void Level::HandleInput(const InputState* pInput)
{
	m_pPlayerShip->HandleInput(pInput);
}


void Level::Update(const GameTime* pGameTime)
{
	for (unsigned int i = 0; i < m_totalSectorCount; i++)
	{
		m_pSectors[i].clear();
	}

	m_gameObjectIt = m_gameObjects.begin();
	for (; m_gameObjectIt != m_gameObjects.end(); m_gameObjectIt++)
	{
		GameObject* pGameObject = (*m_gameObjectIt);
		pGameObject->Update(pGameTime);
	}

	for (unsigned int i = 0; i < m_totalSectorCount; i++)
	{
		if (m_pSectors[i].size() > 1)
		{
			CheckCollisions(m_pSectors[i]);
		}
	}

	m_pKillsCounter->Update(pGameTime);

}


void Level::UpdateSectorPosition(GameObject* pGameObject)
{
	Vector2 position = pGameObject->GetPosition();
	//Vector2 previousPosition = pGameObject->GetPreviousPosition();
	Vector2 halfDimensions = pGameObject->GetHalfDimensions();

	int minX = (int)(position.X - halfDimensions.X - 0.5f);
	int maxX = (int)(position.X + halfDimensions.X + 0.5f);
	int minY = (int)(position.Y - halfDimensions.Y - 0.5f);
	int maxY = (int)(position.Y + halfDimensions.Y + 0.5f);

	//// Expand to contain the previous positions
	//minX = Math::Min(minX, (int)(previousPosition.X - halfDimensions.X - 0.5f));
	//maxX = Math::Max(maxX, (int)(previousPosition.X + halfDimensions.X + 0.5f));
	//minY = Math::Min(minY, (int)(previousPosition.Y - halfDimensions.Y - 0.5f));
	//maxY = Math::Max(maxY, (int)(previousPosition.Y + halfDimensions.Y + 0.5f));

	minX = (int)Math::Clamp(0, m_sectorCount.X - 1, minX / (int)m_sectorSize.X);
	maxX = (int)Math::Clamp(0, m_sectorCount.X - 1, maxX / (int)m_sectorSize.X);
	minY = (int)Math::Clamp(0, m_sectorCount.Y - 1, minY / (int)m_sectorSize.Y);
	maxY = (int)Math::Clamp(0, m_sectorCount.Y - 1, maxY / (int)m_sectorSize.Y);


	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			int index = y * (int)m_sectorCount.X + x;

			m_pSectors[index].push_back(pGameObject);
		}
	}
}

PowerUp* Level::GetPowerUp()
{
	m_powerUpIt = m_PowerUps.begin();
	for (; m_powerUpIt != m_PowerUps.end(); m_powerUpIt++)
	{
		PowerUp* pPowerUp = *m_powerUpIt;
		if (!pPowerUp->IsActive()) return pPowerUp;
	}

	return nullptr;
}



void Level::CheckCollisions(std::vector<GameObject*>& gameObjects)
{
	const unsigned int objectCount = (unsigned int)gameObjects.size();

	GameObject* pFirst, * pSecond;

	for (unsigned int i = 0; i < objectCount - 1; i++)
	{
		pFirst = gameObjects[i];
		if (pFirst->IsActive())
		{
			for (unsigned int j = i + 1; j < objectCount; j++)
			{
				if (!pFirst->IsActive()) continue;

				pSecond = gameObjects[j];
				if (pSecond->IsActive())
				{
					m_pCollisionManager->CheckCollision(pFirst, pSecond);
				}
			}
		}
	}
}

void Level::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->Begin();

	pSpriteBatch->Draw(m_pTexture, m_texturePosition, Color::White, m_pTexture->GetCenter()); // Draw background


	m_gameObjectIt = m_gameObjects.begin();
	for (; m_gameObjectIt != m_gameObjects.end(); m_gameObjectIt++)
	{
		GameObject* pGameObject = (*m_gameObjectIt);
		pGameObject->Draw(pSpriteBatch);
	}

	m_pKillsCounter->Draw(pSpriteBatch);

	pSpriteBatch->End();
}