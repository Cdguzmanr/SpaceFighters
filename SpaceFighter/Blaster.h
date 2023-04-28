
#pragma once

#include "Weapon.h"

class Blaster : public Weapon
{

public:

	Blaster(const bool isActive) : Weapon(isActive)
	{
		m_cooldown = 0;
		 m_cooldownSeconds = 0.35;
	}

	virtual ~Blaster() { }

	virtual void Update(const GameTime *pGameTime)
	{
		if (m_cooldown > 0) m_cooldown -= pGameTime->GetTimeElapsed();
	}

	virtual bool CanFire() const { return m_cooldown <= 0; }

	virtual void ResetCooldown() { m_cooldown = 0; }

	virtual float GetCooldownSeconds() { return m_cooldownSeconds; }

	virtual void SetCooldownSeconds(const float seconds) { m_cooldownSeconds = seconds; }

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


private:

	float m_cooldown;
	
//protected:
public: //temporarily made Blaster::m_cooldownSeconds public for testing //todo undo change Blaster.h line 58
	static float m_cooldownSeconds;//unsure if it should be static

};