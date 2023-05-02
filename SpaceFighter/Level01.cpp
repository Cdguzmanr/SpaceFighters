

#include "Level01.h"
#include "BioEnemyShip.h"


void Level01::SetBackgroundTexture(Texture* pTexture)
{
	m_pBackgroundTexture = pTexture;

}

void Level01::LoadContent(ResourceManager *pResourceManager)
{

	// Load background image - First method
	//Texture* pBackgroundTexture = pResourceManager->Load<Texture>("Textures\\space-galaxy-background.jpg");

	// Load background texture
	Texture* pBackgroundTexture = pResourceManager->Load<Texture>("Textures\\background-space.png"); // doesn't work yet
	SetBackgroundTexture(pBackgroundTexture);

	// Setup enemy ships
	Texture *pTexture = pResourceManager->Load<Texture>("Textures\\BioEnemyShip.png");

	const int COUNT = 21;

	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.3, 0.25, 0.35, 0.2, 0.4,
		0.7, 0.75, 0.65, 0.8, 0.6,
		0.5, 0.4, 0.6, 0.45, 0.55
	};
	
	double delays[COUNT] =
	{
		0.0, 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.5, 0.3, 0.3, 0.3, 0.3
	};

	float delay = 5.0; // start delay -- Default 3.0
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += delays[i];
		position.Set(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		BioEnemyShip *pEnemy = new BioEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		pEnemy->Initialize(position, (float)delay);
		AddGameObject(pEnemy);
	}

	Level::LoadContent(pResourceManager);



}


