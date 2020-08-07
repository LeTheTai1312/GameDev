#pragma once
#include "../Utilities/utilities.h"
#include "Box2D/Box2D.h"

class Game
{
public:
	Game(void);
	~Game(void);
	static Game* GetInstance();
	void Update(ESContext* esContext, float deltaTime);

private:
	static Game* s_Instance;
};

