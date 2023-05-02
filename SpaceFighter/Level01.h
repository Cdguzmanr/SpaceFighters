#pragma once

#include "Level.h"

class Level01 :	public Level
{

public:
	
	//Level01() { }




	virtual ~Level01() { }
	


	virtual void LoadContent(ResourceManager *pResourceManager);


	virtual void UnloadContent() { }

		//this is for: m_pBackgroundTexture = pTexture;
	Texture* m_pBackgroundTexture;
	void SetBackgroundTexture(Texture* pTexture);



private :

	//store the background texture
	//Texture* m_pBackgroundTexture;

	//ResourceManager* m_pResourceManager = nullptr;

};

