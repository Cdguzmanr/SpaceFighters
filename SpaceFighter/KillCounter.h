#pragma once
#include "GameObject.h"



class KillCounter : public GameObject
{
	public:
		KillCounter() { } //  constructor
		virtual ~KillCounter() { } // destructor

		virtual void Draw(SpriteBatch* pSpriteBatch); 

		virtual void LoadContent(ResourceManager* pResourceManager); 
		virtual void Update(const GameTime* pGameTime); // to be defined in cpp

	
		virtual std:: string ToString() const { return "KillCounter"; } // could be const
	
		virtual CollisionType GetCollisionType() const { return (CollisionType::NONE | CollisionType::NONE); }



private: 

	std:: string m_text;

	bool m_isDisplayed;

	Font* m_pFont;

	Color m_color;

	//set transparency of text
	float m_alpha;

	Vector2 m_position;

	Vector2 m_textOffset;

	TextAlign m_textAlign;



};

