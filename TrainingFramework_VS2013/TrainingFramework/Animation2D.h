#pragma once
#include "../Utilities/utilities.h"
#include "Texture.h"
#include "model.h"
#include "Shaders.h"
#include <vector>

using namespace std;

class Animation2D
{
public:
	Animation2D(const char* fileName);
	~Animation2D();

	void play(Texture spriteTexture);
	void set_animation_speed(float newSpeed);
	Shaders anim_shader;
	model model;
	double anim_cursor;
	int curent_frame_indx;
	int frames_count;
	float speed;

	vector<vector<float>> frames;

private:
};
