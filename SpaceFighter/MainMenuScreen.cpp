
#include <string>
#include "MainMenuScreen.h"
#include "GameplayScreen.h"

// Callback Functions
void OnStartGameSelect(MenuScreen *pScreen)
{
	pScreen->GetScreenManager()->AddScreen(new GameplayScreen());
}

void OnQuitSelect(MenuScreen *pScreen)
{
	MainMenuScreen *pMainMenuScreen = (MainMenuScreen *)pScreen;
	pMainMenuScreen->SetQuitFlag();
	pMainMenuScreen->Exit();
}

void OnScreenRemove(Screen *pScreen)
{
	MainMenuScreen *pMainMenuScreen = (MainMenuScreen *)pScreen;
	if (pMainMenuScreen->IsQuittingGame()) pScreen->GetGame()->Quit();
}



MainMenuScreen::MainMenuScreen()
{
	m_pTexture = nullptr;

	SetRemoveCallback(OnScreenRemove);

	SetTransitionInTime(3.0f); // Default - 1.0
	SetTransitionOutTime(0.5f);

	Show(); // Show the screen
}

void MainMenuScreen::LoadContent(ResourceManager *pResourceManager)
{
	// Logo
	m_pTexture = pResourceManager->Load<Texture>("Textures\\Logo.png");
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

	// Create the menu items
	const int COUNT = 2;
	MenuItem *pItem;
	Font::SetLoadSize(20, true);					// Changed Font  // arial.ttf
	Font *pFont = pResourceManager->Load<Font>("Fonts\\Ethnocentric.ttf"); 

	SetDisplayCount(COUNT);

	enum Items { START_GAME, QUIT };
	std::string text[COUNT] = { "Start Game", "Quit"};

	for (int i = 0; i < COUNT; i++)
	{
		pItem = new MenuItem(text[i]);
		pItem->SetPosition(Vector2(100, 100 + 50 * i));
		pItem->SetFont(pFont);
		pItem->SetColor(Color::Blue); // ??
		pItem->SetSelected(i == 0);
		AddMenuItem(pItem);
	}

	GetMenuItem(START_GAME)->SetSelectCallback(OnStartGameSelect);
	GetMenuItem(QUIT)->SetSelectCallback(OnQuitSelect);
}

void MainMenuScreen::Update(const GameTime *pGameTime)
{
	MenuItem *pItem;

	// Set the menu item colors
	for (int i = 0; i < GetDisplayCount(); i++)
	{
		pItem = GetMenuItem(i);
		pItem->SetAlpha(GetAlpha());

		if (pItem->IsSelected()) pItem->SetColor(Color::Cyan);
		else pItem->SetColor(Color::Gold);
	}

	MenuScreen::Update(pGameTime);
}

void MainMenuScreen::Draw(SpriteBatch *pSpriteBatch)
{
	pSpriteBatch->Begin();
	pSpriteBatch->Draw(m_pTexture, m_texturePosition, Color::White * GetAlpha(), m_pTexture->GetCenter());
	pSpriteBatch->End();

	MenuScreen::Draw(pSpriteBatch);
}
