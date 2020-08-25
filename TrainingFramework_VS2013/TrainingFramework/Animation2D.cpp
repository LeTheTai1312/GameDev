#include "stdafx.h"
#include "Animation2D.h"
#include <string>

Animation2D::Animation2D(){

}

Animation2D::~Animation2D()
{
}

void Animation2D::play()
{
	vector<float> frame = Singleton<ResourceManager>::GetInstance()->frames[frameNum];
	//nomalization
	frame[0] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
	frame[1] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;
	frame[2] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
	frame[3] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;

	modela.vertices[0].uv.x = frame[0] + frame[2]; modela.vertices[0].uv.y = frame[1];
	modela.vertices[1].uv.x = frame[0] + frame[2]; modela.vertices[1].uv.y =  (frame[1] + frame[3]) ;
	modela.vertices[2].uv.x = frame[0]; modela.vertices[2].uv.y =  (frame[1] + frame[3]);
	modela.vertices[3].uv.x = frame[0]; modela.vertices[3].uv.y =  frame[1];

	
	//glGenBuffers(1, &modela->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, modela.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*glGenBuffers(1, &model.iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, model.indices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
}	


void Animation2D::set_animation_speed(float newSpeed)
{
	speed = newSpeed;
}

void Animation2D::draw_anim()
{
	//camera.set_CamVP();
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//play();
	set_matrix(Singleton<Camera>::GetInstance()->camera_VP);
	glUseProgram(shaders.program);
	glUniformMatrix4fv(shaders.WVP, 1, GL_FALSE, &wvpMatrix.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modela.iboId);

	glBindTexture(GL_TEXTURE_2D, Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].textureID);
	glUniform1i(glGetUniformLocation(shaders.program, "u_texture"), 0);

	if (shaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(shaders.positionAttribute);
		glVertexAttribPointer(shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (shaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(shaders.uvAttribute);
		glVertexAttribPointer(shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)
			+ sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
	}

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Animation2D::update(float deltaTime)
{
	anim_cursor += deltaTime;
	dtTm = deltaTime;
	frame_wait += deltaTime;
	
	if (anim_cursor > speed) {
		curent_frame_indx = (curent_frame_indx + 1) % frames_count;
		anim_cursor = 0;
		//vector<float> frame = frames[curent_frame_indx];
		vector<float> frame = Singleton<ResourceManager>::GetInstance()->frames[frameNum];
		//nomalization
		frame[0] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
		frame[1] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;
		frame[2] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].width;
		frame[3] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[curent_texture].height;

		modela.vertices[0].uv.x = (modela.vertices[0].uv.x + frame[2]); modela.vertices[0].uv.y = frame[1];
		modela.vertices[1].uv.x = (modela.vertices[1].uv.x + frame[2]); modela.vertices[1].uv.y = (frame[1] + frame[3]);
		modela.vertices[2].uv.x = (modela.vertices[2].uv.x + frame[2]); modela.vertices[2].uv.y = (frame[1] + frame[3]);
		modela.vertices[3].uv.x = (modela.vertices[3].uv.x + frame[2]); modela.vertices[3].uv.y = frame[1];

		glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, modela.vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Animation2D::load_element(const char* fileName){
	int index;
	anim_cursor = 0;
	curent_frame_indx = 0;
	frame_wait = 0;
	signal = 0;

	//fclose(file);
	modela.init("../Resources/Models/animation.nfg");
	//model a = model(Singleton<ResourceManager>::GetInstance()->models[models]);
}
int c = 0;
void Animation2D::update_animation_move_player(int x, int y)
{
	int v = 3;//vận tốc tính theo pixel ban đầu mặc định
	float a = (txw + 1.5) * Globals::screenWidth / 3;
	float b = (1.5 - tyw) * Globals::screenHeight / 3;//toa do vi tri cua player hien tai tinh theo pixel
	
	//vector chi huong chuyen dong 
	float j = x - a;
	float k = y - b;

	// đoạn xét cá quay đầu
	if (j <= 0 && c == 0) {
		play();
		//curent_texture = texture[2];
		curent_texture = texture[1];
		signal = 1;
		c = 1;
	}
	else if (j > 0 && c == 1) {
		play();
		curent_texture = texture[0];
		signal = 0;
		c = 0;
	}

	// vận tốc di chuyển
	float c = v * (float)j / sqrt(j * j + k * k);
	float d = v * (float)k / sqrt(j * j + k * k);
	m_vx = c;m_vy = d;
	//vị trí sau khi di chuyển
	a += c;
	b += d;
	// gán vị trí mới
	txw = ((float)a / Globals::screenWidth) * 3.0 - 1.5;
	tyw = -(((float)b / Globals::screenHeight) * 3.0 - 1.5);

}

void Animation2D::update_animation_move_boss()
{
	int v = 3;//vận tốc tính theo pixel ban đầu mặc định
	float a = (txw + 1.5) * Globals::screenWidth / 3;
	float b = (1.5 - tyw) * Globals::screenHeight / 3;//toa do vi tri cua player hien tai tinh theo pixel
	float j, k;
	if (a > 0) {
		j = 1;k = 0;
	}
	else {
		j = -1; k = 0;
	}

	if (j <= 0 && c == 0) {
		play();
		curent_texture = texture[1];
		signal = 1;
		c = 1;
		cout << c;
	}
	else if (j > 0 && c == 1) {
		play();
		curent_texture = texture[0];
		signal = 0;
		c = 0;
		cout << c;
	}


	float c = v * (float)j / sqrt(j * j + k * k);
	float d = v * (float)k / sqrt(j * j + k * k);
	m_vx = c; m_vy = d;
	a += c;//vị trí sau khi di chuyển
	b += d;

	txw = ((float)a / Globals::screenWidth) * 3.0 - 1.5;
	tyw = -(((float)b / Globals::screenHeight) * 3.0 - 1.5);

}

