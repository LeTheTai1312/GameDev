#include "stdafx.h"
#include "Game.h"

Game* Game::s_Instance = NULL;

Game::Game(void)
{
}

Game::~Game(void)
{
}

Game* Game::GetInstance() {
	if (!s_Instance) 
		s_Instance = new Game();
	return s_Instance;
}

void Game::Update(ESContext* esContext, float deltaTime) {

}