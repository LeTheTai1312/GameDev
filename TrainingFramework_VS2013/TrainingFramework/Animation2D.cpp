#include "stdafx.h"
#include "Animation2D.h"
#include <string>

Animation2D::Animation2D(const char* fileName)
	:anim_cursor(0),
	curent_frame_indx(0),
	speed(0.05f)
{
	float a, b, c, d;
	FILE* file;

	file = fopen(fileName, "r");
	for (int i = 0; i < 11; i++) {
		vector<int> result;
		fscanf(file, "%f,%f,%f,%f\n", &a, &b, &c, &d);
		result.push_back(a);
		result.push_back(b);
		result.push_back(c);
		result.push_back(d);
		vector<float> frame;
		frame.push_back(result[0]);
		frame.push_back(result[1]);
		frame.push_back(result[2]);
		frame.push_back(result[3]);
		frames.push_back(frame);
	}

	frames_count = (int)frames.size();

	fclose(file);
}

Animation2D::~Animation2D()
{
}

void Animation2D::play(Texture spriteTexture)
{
	vector<float> frame = frames[0];

	//nomalization
	frame[0] /= spriteTexture.width;
	frame[1] /= spriteTexture.height;
	frame[2] /= spriteTexture.width;
	frame[3] /= spriteTexture.height;

	model.vertices = new Vertex[4];

	model.vertices[0].pos.x = 1.0f; model.vertices[0].pos.y = 1.0f; model.vertices[0].pos.z = 0.0f;
	model.vertices[1].pos.x = 1.0f; model.vertices[1].pos.y = -1.0f; model.vertices[1].pos.z = 0.0f;
	model.vertices[2].pos.x = -1.0f; model.vertices[2].pos.y = -1.0f; model.vertices[2].pos.z = 0.0f;
	model.vertices[3].pos.x = -1.0f; model.vertices[3].pos.y = 1.0f; model.vertices[3].pos.z = 0.0f;


	model.vertices[0].uv.x = frame[0] + frame[2]; model.vertices[0].uv.y = 1 - frame[1];
	model.vertices[1].uv.x = frame[0] + frame[2]; model.vertices[1].uv.y = 1 - (frame[1] + frame[3]) ;
	model.vertices[2].uv.x = frame[0]; model.vertices[2].uv.y = 1 - (frame[1] + frame[3]);
	model.vertices[3].uv.x = frame[0]; model.vertices[3].uv.y = 1 - frame[1];

	model.indices = new int[6];
	model.indices[0] = 0; model.indices[1] = 1; model.indices[2] = 2;
	model.indices[3] = 0; model.indices[4] = 2; model.indices[5] = 3;
	
	glGenBuffers(1, &model.vboId);
	glBindBuffer(GL_ARRAY_BUFFER, model.vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, model.vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model.iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, model.indices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	anim_shader.Init("../Resources/Shaders/MulTextureVS.vs", "../Resources/Shaders/MulTextureFS.fs");
}	


void Animation2D::set_animation_speed(float newSpeed)
{
	speed = newSpeed;
}
