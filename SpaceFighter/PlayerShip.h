
#pragma once

#include "Ship.h"
#include "PowerUp.h"



class PlayerShip : public Ship
{

public:

	PlayerShip() { }
	virtual ~PlayerShip() { }

	virtual void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

	virtual void SetWeaponTexture(Texture* pTexture) { m_pTexture = pTexture; }

	virtual void LoadContent(ResourceManager *pResourceManager);

	virtual void Update(const GameTime *pGameTime);

	virtual void Draw(SpriteBatch *pSpriteBatch);

	virtual void HandleInput(const InputState *pInput);

	virtual void Initialize(Level *pLevel, Vector2 &startPosition);

	virtual Vector2 GetHalfDimensions() const;

	virtual void SetDesiredDirection(const Vector2 direction) { m_desiredDirection.Set(direction); }

	virtual std::string ToString() const { return "Player Ship"; }

	virtual CollisionType GetCollisionType() const { return (CollisionType::PLAYER | CollisionType::SHIP); }

	virtual void ConfineToScreen(const bool isConfined = true) { m_isConfinedToScreen = isConfined; }

	virtual PowerUp::PowerUpType GetPowerUpType(PowerUp::PowerUpType &m_pType) 
	{
		PowerUp::PowerUpType type = *&m_pType;
		return type;
	}

	// We should modify PlayerShip boos instead of Blaster directly
	virtual void SetBoost(float &m_pRapidFireRate) 
	{
		float boost;
		boost = *&m_pRapidFireRate;
	}

	


protected:

	virtual void SetResponsiveness(const float responsiveness);

	virtual float GetResponsiveness() const { return m_responsiveness; }

	virtual Vector2 GetDesiredDirection() const { return m_desiredDirection; }


private:

	Vector2 m_desiredDirection;
	Vector2 m_velocity;

	float m_responsiveness = 0;

	bool m_isConfinedToScreen = false;

	Texture *m_pTexture = nullptr;

	Texture* m_pBulletTexture = nullptr;

};