#include "PowerUp.h"
#include <random>
#include "Blaster.h"
#include "Level.h"

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
	PowerUpTimer(pGameTime);

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


void PowerUp::SpeedBooster() 
{
	GetSpeedBoostType();
	SpeedBoostIsActive = true;
	if (isActive != false)
	{
		if (SpeedBoostType == 1) //rand 
		{
			SetRandFireRate();
		}
		else if (SpeedBoostType == 2) //double
		{
			m_SpeedBoostAmount = 2;
		}
		else if (SpeedBoostType == 3) //triple
		{
			m_SpeedBoostAmount = 3;
		}
	}
}


void PowerUp::RapidFireMethod()
{
	GetRapidFireType();
	RapidFireIsActive = true;
	if (isActive != false)
	{
		if (isStackable == true)
		{
			if (m_RapidFireRate <= 8)
			{
				if (RapidFireType == 4 && isStackable == true) //double stack
				{
					m_RapidFireRate += 2;
				}
				else if (RapidFireType == 5 && isStackable == true) //triple stack
				{
					m_RapidFireRate += 3;
				}
				else if (RapidFireType == 6 && isStackable == true) //triple stack
				{
					m_RapidFireRate += SetRandFireRate();
				}
			}
		}
		else
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

void PowerUp::GetSpeedBoostType()
{
	int min = 1;
	int max = 3;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max); //todo:adjust min and max
	SpeedBoostType = dis(gen);
}



float PowerUp::SetRandFireRate() {
	float min = 2.0;
	float max = 3.0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	m_RapidFireRate = randFireRate;
	return m_RapidFireRate;
}

void PowerUp::ActivatePowerUp()
{
	
	if (m_type == SpeedBoost) { isActive = true; SpeedBooster(); }
		else if (m_type == RapidFire) { isActive = true; RapidFireMethod(); }
		//else if (m_type == Shield) {}
		//else if (m_type == ExtraDamage) {}	
}

void PowerUp::PowerUpTimer(const GameTime* pGameTime)
{

	if (isActive == true)
	{
    	powerUpDuration -= pGameTime->GetTimeElapsed();
		if (powerUpDuration <= 0)
		{
 			isActive = false;
			timerIsStarted = false;
			DeactivatePowerUp();
		}
	}
}

void PowerUp::DeactivatePowerUp()
{
	if (RapidFireIsActive == true)
	{
		m_RapidFireRate = 1;
		RapidFireIsActive = false;
	}
	if (SpeedBoostIsActive == true)
	{
		m_SpeedBoostAmount = 1;
		SpeedBoostIsActive = false;
	}
	m_type = none;
	powerUpDuration = 6;
}

float PowerUp::SetRandSpeedBoost()
{
	float min = 1.0;
	float max = 3.0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	m_SpeedBoostAmount = randFireRate;
	return m_SpeedBoostAmount;
}
//////git g

