#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Animation2D.h"
#include <vector>
class Animation2D;
using namespace std;

class SceneManager
{
public:
	Objects* objects;
	Animation2D* anim;
	int objectNum;
	//int textureNum;
	//int cubeTextureNum;
	int animNum;
	void loadObjects(char *l);
	void draw();
	void update_animation(float);
	void mouse_animation_move(int x, int y);
	void free();
	SceneManager();
	~SceneManager();
	void CheckCollision(Rectangl rect1, Rectangl rect2);// va chạm giữa các điểm thể hiện mồm con cá thứ nhất và con cá thứ 2
	void CheckCollision(Rectangl rect, Circle cir);// va chạm giữa điểm chính giữa con cá thứ nhất và vòng tròn báo hiệu của con cá thứ 2

	static SceneManager* GetInstance(float);
private:
	static SceneManager* s_Instance;
};

