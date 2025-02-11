#pragma once

#include "GameObject.h"
#include "BioEnemyShip.h"
//powerup needs to know about level then level knows about playership and can be used to get the blaster instance to affect it
class PlayerShip;

class PowerUp : public GameObject
{
	
public:
	enum PowerUpType {
		none = 0,
		SpeedBoost = 1,
		RapidFire = 2,
		
		Shield,
		ExtraDamage
	};

	//todo get the methods built

	PowerUp();

	virtual void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

	virtual void Update(const GameTime* pGameTime);

	virtual void Draw(SpriteBatch* pSpriteBatch);

	virtual CollisionType GetCollisionType() const { return CollisionType::POWERUP | CollisionType::PLAYER; }

	virtual void Initialize(const Vector2 position, const double delaySeconds);

	virtual float GetSpeed() const { return m_speed; }

	virtual void SetSpeed(const float speed) { m_speed = speed; }

	virtual PowerUpType GetType() const { return m_type; }

	virtual void SetType(const PowerUpType type) { m_type = type; }

	virtual std::string ToString() const { return "PowerUp"; }


	virtual float GetRapidFireRate() { return m_RapidFireRate; }

	virtual void RapidFireMethod();

	virtual void GetRapidFireType();

	virtual float SetRandFireRate();


	virtual void GetSpeedBoostType();

	virtual void SpeedBooster();

	virtual float GetSpeedBoost() { return m_SpeedBoostAmount; }

	virtual float SetRandSpeedBoost();


	virtual void ActivatePowerUp();

	virtual void PowerUpTimer(const GameTime* pGameTime);

	virtual void DeactivatePowerUp();


private:
	double m_delaySeconds;

	double m_activationSeconds;

	float m_speed;

	float m_duration;

	PowerUpType m_type;
	

	Texture* m_pTexture = nullptr;

	
	bool isActive;

	bool SpeedBoostIsActive = false;
	int SpeedBoostType;
	float m_SpeedBoostAmount = 1;
	float RandSpeedBoostAmount;
	
	bool RapidFireIsActive = false;
	int RapidFireType;
	float m_RapidFireRate = 1.0;
	bool isStackable;
	float randFireRate;

	bool timerIsStarted = false;
	double start;
	double end;
	float powerUpDuration = 6;
};

