#pragma once

#include "Level.h"

class Level01 :	public Level
{

public:

	//Level01() { }




	virtual ~Level01() { }
	


	virtual void LoadContent(ResourceManager* pResourceManager)
	{

		// Load background texture
		//m_pBackgroundTexture = pResourceManager->Load<Texture>("Textures\\background-space.png");
		//m_texturePosition = Game::GetScreenCenter();



		// Setup enemy ships
		Texture* pTexture = pResourceManager->Load<Texture>("Textures\\BioEnemyShip.png");



		const int COUNT = 21;

		double xPositions[COUNT] =
		{
			0.25, 0.2, 0.3,
			0.75, 0.8, 0.7,
			0.3, 0.25, 0.35, 0.2, 0.4,
			0.7, 0.75, 0.65, 0.8, 0.6,
			0.5, 0.4, 0.6, 0.45, 0.55
		};

		double delays[COUNT] =
		{
			0.0, 0.25, 0.25,
			3.0, 0.25, 0.25,
			3.25, 0.25, 0.25, 0.25, 0.25,
			3.25, 0.25, 0.25, 0.25, 0.25,
			3.5, 0.3, 0.3, 0.3, 0.3
		};

		float delay = 5.0; // start delay -- Default 3.0
		Vector2 position;

		for (int i = 0; i < COUNT; i++)
		{
			delay += delays[i];
			position.Set(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

			BioEnemyShip* pEnemy = new BioEnemyShip();
			pEnemy->SetTexture(pTexture);
			pEnemy->SetCurrentLevel(this);
			pEnemy->Initialize(position, (float)delay);
			AddGameObject(pEnemy);
		}

		Level::LoadContent(pResourceManager);



	}


	virtual void UnloadContent() { }

	



private :

	//store the background texture
	//Texture* m_pBackgroundTexture;
	//Vector2 m_texturePosition;

	//ResourceManager* m_pResourceManager = nullptr;

};

