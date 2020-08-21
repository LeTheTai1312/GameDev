// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include"../Include/Box2D/Box2D.h"
//#include "../Include/GL/glut.h"
//#include"esUtil.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "model.h"
#include "Texture.h"
#include "Object.h"
#include "Matran.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Singleton.h"
#include "Sprite2D.h"
#include "Animation2D.h"
#include <conio.h>
#include <iostream>

#define GLUT_LEFT_BUTTON 0
#define GLUT_MIDDLE_BUTTON 1
#define GLUT_RIGHT_BUTTON 2

using namespace std;
GLuint vboId, iboId, textureID, matrixID;
Shaders myShaders;
Matran matrix;


int Init ( ESContext *esContext )
{
	glClearColor (1.0f, 0.5f, 1.0f, 1.0f );
	Singleton<ResourceManager>::GetInstance()->loadResource("../Resources/Resource.txt");
	Singleton<SceneManager>::GetInstance()->loadObjects("../Resources/Scene.txt");
	return 0;
}

void Draw ( ESContext *esContext)
{
	Singleton<Game>::GetInstance()->Draw();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime)
{
	Singleton<Game>::GetInstance()->Update_animation(deltaTime);
	Singleton<Game>::GetInstance()->Update(deltaTime);
}

void TouchActionDown(ESContext* esContext, int x, int y)
{
	// Mouse down
	cout << x << "-" << y<<endl;
}

void TouchActionUp(ESContext* esContext, int x, int y)
{
	// Mouse up
}

void TouchActionMove(ESContext* esContext, int x, int y)
{
	// Mouse move
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	Singleton<Game>::GetInstance()->Key(key, bIsPressed);
}

void CleanUp()
{	
	for (int i = 0; i < Singleton<ResourceManager>::GetInstance()->modelsNum; i++) {
		glDeleteBuffers(1, &Singleton<ResourceManager>::GetInstance()->models[i].vboId);
		glDeleteBuffers(1, &Singleton<ResourceManager>::GetInstance()->models[i].iboId);
	}
	for (int i = 0; i < Singleton<ResourceManager>::GetInstance()->modelsNum; i++) {
		Singleton<ResourceManager>::GetInstance()->free();
	}
	//glDeleteBuffers(1, &Singleton<Sprite2D>::GetInstance()->anim->model.vboId);
	//glDeleteBuffers(1, &Singleton<Sprite2D>::GetInstance()->anim->model.iboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	/*esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);*/

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

