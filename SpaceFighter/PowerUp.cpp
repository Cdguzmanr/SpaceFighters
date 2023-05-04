#include "PowerUp.h"

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

// generates a random PowerUpType enum value and sets it as the current type for the power-up.
//not sure whether to use SetType or Return 
void PowerUp::GetPowerUpRandom()
{
	int random = rand() % 4 + 1; 
	switch (random)
	{
	case 1:
		SetType(PowerUpType::RapidFire);
		break;
	case 2:
		SetType(PowerUpType::SpeedBoost);
		break;
	case 3:
		SetType(PowerUpType::Shield);
		break;
	case 4:
		SetType(PowerUpType::ExtraDamage);
		break;
	default:
		break;
	}
}