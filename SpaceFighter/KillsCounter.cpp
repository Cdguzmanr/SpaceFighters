#include "KillsCounter.h"



void KillsCounter::LoadContent(ResourceManager* pResourceManager)
{

	m_pFont = pResourceManager->Load<Font>("Fonts\\Ethnocentric.ttf");

	m_text = "Score :  " + std::to_string(GetKillsCounter());
	m_color = Color::Khaki;
	m_alpha = 1.0f;

	m_position = Vector2::ZERO;
	m_textOffset = Vector2::ZERO;

	m_textAlign = TextAlign::LEFT;
}


void KillsCounter::Draw(SpriteBatch* pSpriteBatch)
{
	pSpriteBatch->DrawString(m_pFont, &m_text, Vector2(700, 10), m_color * m_alpha, m_textAlign);

}	
void KillsCounter::Update(const GameTime *pGameTime)
{
	m_text = "Score :  " + std::to_string(GetKillsCounter());
	GameObject::Update(pGameTime);

}