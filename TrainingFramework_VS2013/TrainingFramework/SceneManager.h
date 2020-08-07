#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include <vector>

class SceneManager
{
public:
	int objectNum, textureNum, cubeTextureNum;
	Objects* objects;
	Camera camera;
	void loadObjects(char *l);
	void draw();
	void free();
	SceneManager();
	~SceneManager();
	static SceneManager* GetInstance();
private:
	static SceneManager* s_Instance;
};

