#include "stdafx.h"
#include "Game.h"

using namespace std;


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

void Game::Update(float deltaTime) {
	if (MoveF) {
		cout << "forward" << endl;
		Singleton<SceneManager>::GetInstance()->camera.movementF(deltaTime);
		MoveF = false;
	}
	if (MoveB) {
		cout << "Back" << endl;
		Singleton<SceneManager>::GetInstance()->camera.movementB(deltaTime);
		MoveB = false;
	}
	if (MoveL) {
		cout << "Left" << endl;
		Singleton<SceneManager>::GetInstance()->camera.movementL(deltaTime);
		MoveL = false;
	}
	if (MoveR) {
		cout << "Right" << endl;
		Singleton<SceneManager>::GetInstance()->camera.movementR(deltaTime);
		MoveR = false;
	}
	if (MoveU) {
		cout << "Up" << endl;
		Singleton<SceneManager>::GetInstance()->camera.movementU(deltaTime);
		MoveU = false;
	}
	if (MoveD) {
		cout << "Down" << endl;
		Singleton<SceneManager>::GetInstance()->camera.movementD(deltaTime);
		MoveD = false;
	}
	if (RotateL) {
		cout << "RLeft" << endl;
		Singleton<SceneManager>::GetInstance()->camera.rotationsL(deltaTime);
		RotateL = false;
	}
	if (RotateR) {
		cout << "RRight" << endl;
		Singleton<SceneManager>::GetInstance()->camera.rotationsR(deltaTime);
		RotateR = false;
	}
	if (RotateD) {
		cout << "RDown" << endl;
		Singleton<SceneManager>::GetInstance()->camera.rotationsD(deltaTime);
		RotateD = false;
	}
	if (RotateU) {
		cout << "RUp" << endl;
		Singleton<SceneManager>::GetInstance()->camera.rotationsU(deltaTime);
		RotateU = false;
	}
}

void Game::Key( unsigned char key, bool bIsPressed){
	if (key == 0x51 && bIsPressed && !MoveF) MoveF = true;
	if (key == 0x45 && bIsPressed && !MoveB) MoveB = true;
	if (key == 0x41 && bIsPressed && !RotateL) RotateL = true;
	if (key == 0x44 && bIsPressed && !RotateR) RotateR = true;
	if (key == 0x53 && bIsPressed && !RotateD) RotateD = true;
	if (key == 0x57 && bIsPressed && !RotateU) RotateU = true;
	if (key == VK_LEFT && bIsPressed && !MoveL) MoveL = true;
	if (key == VK_RIGHT && bIsPressed && !MoveR) MoveR = true;
	if (key == VK_UP && bIsPressed && !MoveU) MoveU = true;
	if (key == VK_DOWN && bIsPressed && !MoveD) MoveD = true;
}

void Game::Draw(){

	Singleton<SceneManager>::GetInstance()->draw();
}