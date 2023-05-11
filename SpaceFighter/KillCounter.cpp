#include "KillCounter.h"

using namespace std;

void KillCounter::LoadContent(ResourceManager* pResourceManager)
{
	m_pFont = pResourceManager->Load<Font>("Fonts\\Ethnocentric.tff");
	
	
	m_color = Color::Yellow;
	m_alpha= 1.0f;
	m_position = Vector2::ZERO; // could be zero
	m_textOffset = Vector2::ZERO;	
	m_textAlign = TextAlign::LEFT;

}
void KillCounter::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->DrawString(m_pFont, &m_text, Vector2(700, 10), m_color * m_alpha, m_textAlign);

}

void KillCounter::Update(GameTime* pGameTime)
{
	m_text = ("Kill Counter :  " + to_string(GetCountOfKills()));//
	GameObject::Update(pGameTime);
}

