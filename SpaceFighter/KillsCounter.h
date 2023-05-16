#pragma once
#include "GameObject.h"

class KillsCounter : public GameObject
{
public:
	KillsCounter() {}
	virtual ~KillsCounter(){ }

	/*void IncreaseeKillsCounter();
	int GetKillsCounter() const;*/

	virtual void Draw(SpriteBatch* pSpriteBatch);

	virtual void LoadContent(ResourceManager* pResourceManager);

	virtual void Update(const GameTime* pGameTime);

	virtual std::string ToString() const { return "KillsCounter"; }

	virtual CollisionType GetCollisionType() const { return (CollisionType::NONE | CollisionType::NONE); }

private:
	std::string m_text;

	bool m_isDisplayed;

	Font* m_pFont;

	Color m_color;

	float m_alpha;

	Vector2 m_position;

	Vector2 m_textOffset;

	TextAlign m_textAlign;

};

