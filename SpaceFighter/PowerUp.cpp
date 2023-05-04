#include "PowerUp.h"
#include <random>
#include "Blaster.h"

// code in progress

PowerUp::PowerUp()
{
	SetSpeed(150);
	SetCollisionRadius(20);
}

void PowerUp::Update(const GameTime* pGameTime)
{
	TranslatePosition(0, GetSpeed() * pGameTime->GetTimeElapsed());

	if (!IsOnScreen()) Deactivate();

	if (m_delaySeconds > 0)
	{
		m_delaySeconds -= pGameTime->GetTimeElapsed();

		if (m_delaySeconds <= 0)
		{
			GameObject::Activate();
		}
	}


	if (IsActive())
	{
		m_activationSeconds += pGameTime->GetTimeElapsed();
		if (m_activationSeconds > 2 && !IsOnScreen()) Deactivate();
	}

	GameObject::Update(pGameTime);
}

void PowerUp::Draw(SpriteBatch* pSpriteBatch)
{
	if (IsActive())
	{
		pSpriteBatch->Draw(m_pTexture, GetPosition(), Color::White, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
	}
}

void PowerUp::Initialize(const Vector2 position, const double delaySeconds)
{
	SetPosition(position);
	m_delaySeconds = delaySeconds;
}

//void PowerUp::RandRapidFiring(PlayerShip* playership) {
//	 std::random_device rd;
//	 std::mt19937 gen(rd());
//	 std::uniform_int_distribution<>dis(min, max);
//	 RandRapidFireRate = static_cast<float> (dis(gen)) / 10000.0f;
//	 
//	 //SetCooldownBoost(2);	
//}

void PowerUp::SpeedBooster() {

}

void PowerUp::DoubleRapidFire() 
{
	
}
void PowerUp::RapidFire()
{
	/*getPowerUpType();
	if(PowerUpType == 2)
	{
		GetRapidFireType();
		if(RapidFireType == 1) //rand non-stack
		{
			std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
		}
		elseif(RapidFireType == 2) //double non-stack
		{
			m_RapidFireRate = 2;
		}
		else if(RapidFireType == 1) //triple non-stack
		{
			m_RapidFireRate = 3;
		}
		
	}
	*/
}
/*
GetRapidFireType()
{
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    
    RapidFireType = dis(gen);
}
*/