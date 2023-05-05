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


void PowerUp::RapidFireMethod()
{
	if (m_type == RapidFire)
	{
		//GetRapidFireType();
		m_RapidFireRate = 2;

		if (isStackable == true)
		{
			if (m_RapidFireRate <= 8)
			{
				if (RapidFireType == 1 && isStackable == false) //rand non-stack
				{
					SetRandFireRate();
				}
				else if (RapidFireType == 2 && isStackable == false) //double non-stack
				{
					m_RapidFireRate = 2;
				}
				else if (RapidFireType == 3 && isStackable == false) //triple non-stack
				{
					m_RapidFireRate = 3;
				}
			}
			
			
		}
		else
		{
			if (RapidFireType == 4 && isStackable == true) //triple non-stack
			{
				m_RapidFireRate = 2;
			}
			else if (RapidFireType == 5 && isStackable == true) //triple non-stack
			{
				m_RapidFireRate = 3;
			}
			else if (RapidFireType == 6 && isStackable == true) //triple non-stack
			{
				SetRandFireRate();
			}
			//void ResetPowerUpTimer();
		}
	}
}
		

	


void PowerUp::GetRapidFireType()
{
	int min = 1;
	int max = 6;
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max); //todo:adjust min and max
    
    RapidFireType = dis(gen);
	if (RapidFireType <= 3)
	{
		isStackable = false;
	}
	else {
		isStackable = true;
	}
}



void PowerUp::SetRandFireRate() {
	float min = 2.0;
	float max = 3.0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	m_RapidFireRate = randFireRate;
}
//void ResetPowerUpTimer(){}