#pragma once

#include "GameObject.h"
#include "BioEnemyShip.h"

class PowerUp : public GameObject
{
public:
	enum PowerUpType {
		RapidFire = 1,
		SpeedBoost,
		Shield,
		ExtraDamage
	};

	PowerUp();
	virtual ~PowerUp() { }

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

	virtual void GetPowerUpRandom();
	
private:
	double m_delaySeconds;

	double m_activationSeconds;

	float m_speed;

	float m_duration;

	PowerUpType m_type;
	
	Texture* m_pTexture = nullptr;


};

