#pragma once

#include "GameObject.h"
#include "BioEnemyShip.h"
#include "PlayerShip.h"

class PowerUp : public GameObject
{

public:
	enum PowerUpType {
		RapidFire = 1,
		SpeedBoost,
		stackingFireRate,
		doubleFireRate,
		tripleFireRate,

		//Shield,
		//ExtraDamage
	};
	int boostMultiplier;
	bool activePowerUp;
	//todo get the methods built

	PowerUp();


	//virtual void SetCooldownBoost(const float boost);
	//virtual void RandRapidFiring(PlayerShip* playership);
	virtual void SpeedBooster();
	virtual void PowerUp::StackingFireRate();
	virtual void PowerUp::DoubleFireRate();
	virtual void PowerUp::TripleFireRate();

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

private:
	double m_delaySeconds;

	double m_activationSeconds;

	float m_speed;

	float m_duration;

	PowerUpType m_type;

	Texture* m_pTexture = nullptr;

	float min;
	float max;
	float RandRapidFireRate;
	int boostMultiplier;

};

