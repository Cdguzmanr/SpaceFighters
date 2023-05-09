
#pragma once

#include "Weapon.h"
#include "PowerUp.h"
#include "PlayerShip.h"


class Blaster : public Weapon
{

public:

	Blaster(const bool isActive) : Weapon(isActive)
	{
		// Assignment 6.B Wepon cooldown -- Shoot Faster 
		m_cooldown = 0; 
		m_cooldownSeconds = 0.35 / m_cooldownBoost; // old: 0.35
	}

	virtual ~Blaster() { }

	virtual void Update(const GameTime *pGameTime)
	{
		if (m_cooldown > 0) m_cooldown -= pGameTime->GetTimeElapsed();
	}

	virtual bool CanFire() const { return m_cooldown <= 0; }

	virtual void ResetCooldown() { m_cooldown = 0; }

	virtual float GetCooldownSeconds() { return m_cooldownSeconds; }

	virtual void SetCooldownBoost(const float boost)
	{ 

		m_cooldownBoost = boost;	
	}
	

	virtual void Fire(TriggerType triggerType)
	{
		if (IsActive() && CanFire())
		{
			if (triggerType.Contains(GetTriggerType()))
			{
				Projectile *pProjectile = GetProjectile();
				if (pProjectile)
				{
					AudioSample* pAudio = GetFireSound();
					if (pAudio) pAudio->Play();

					pProjectile->Activate(GetPosition(), true);
					m_cooldown = m_cooldownSeconds;
					
				}
			}
		}
	}
	//void PowerUp::GetType(PlayerShip::PlayerShip playership)


	/*PowerUp::PowerUp();
	* 
	/*PowerUp powerUp = PowerUp();

	virtual PowerUp::PowerUpType GetType(PowerUp::PowerUpType* m_pType) const { return PowerUp::&m_pType; }

	virtual void SetType(const PowerUp::PowerUpType type) { PowerUp::m_pType = type; }
	virtual void SetType(const PowerUp::PowerUpType type) { PowerUp::PowerUpType->m_pType = type; }*/

private:
	
	float m_cooldown;
	float m_cooldownSeconds;
	float m_cooldownBoost;


};