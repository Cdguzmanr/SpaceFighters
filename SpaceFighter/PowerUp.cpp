#include "PowerUp.h"
#include <random>
#include "Blaster.h"
#include "Level.h"
#include <ctime>

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
	PowerUpTimer(pGameTime);
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


void PowerUp::SpeedBooster() {

}


void PowerUp::RapidFireMethod()
{
	GetRapidFireType();
	
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
	else 
	{
		m_RapidFireRate = 1;
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



float PowerUp::SetRandFireRate() {
	float min = 2.0;
	float max = 3.0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	m_RapidFireRate = randFireRate;
	return m_RapidFireRate;
}
//void ResetPowerUpTimer(){}


void PowerUp::ActivatePowerUp()
{
	//if (m_type == SpeedBoost) {}
	if (m_type == RapidFire) { isActive = true; RapidFireMethod(); }
	//else if (m_type == Shield) {}
	//else if (m_type == ExtraDamage) {}
	/*else
	{
		m_type = none;
	}
	
	when timer runs out set poweruptye to none*/
}

void PowerUp::PowerUpTimer(const GameTime* pGameTime)
{

	if (isActive == true)
	{
		
		if (timerIsStarted == false)
		{
			start = pGameTime->GetTimeElapsed();
			timerIsStarted = true;
		}
		end = pGameTime->GetTimeElapsed();

		GetPowerUpDurationCalc();
		if (currentPowerUpDuration >= 6)
		{
			isActive = false;
		}
	}
}

float PowerUp::GetPowerUpDurationCalc()
{
	currentPowerUpDuration = end - start;
	return currentPowerUpDuration;
}


