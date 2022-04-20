#pragma once

#include "Level.h"

class Level02 : public Level
{

public:

	Level02() { }

	virtual ~Level02() { }

	virtual void LoadContent(ResourceManager* pResourceManager);

	virtual void UnloadContent() { }

};

