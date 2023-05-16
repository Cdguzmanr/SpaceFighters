
#pragma once

#include "EnemyShip.h"

class BioEnemyShip : public EnemyShip
{

public:

	BioEnemyShip();
	virtual ~BioEnemyShip() { }

	virtual void SetTexture(Texture *pTexture) { m_pTexture = pTexture; }

	virtual void Update(const GameTime *pGameTime);

	virtual void Draw(SpriteBatch *pSpriteBatch);

	//virtual void Hit(const float damage);

private:

	Texture *m_pTexture = nullptr;

};