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
	vector<float> frame = frames[1];
	//nomalization
	frame[0] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].width;
	frame[1] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].height;
	frame[2] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].width;
	frame[3] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].height;

	modela.vertices[0].uv.x = frame[0] + frame[2]; modela.vertices[0].uv.y = 1 - frame[1];
	modela.vertices[1].uv.x = frame[0] + frame[2]; modela.vertices[1].uv.y = 1 - (frame[1] + frame[3]) ;
	modela.vertices[2].uv.x = frame[0]; modela.vertices[2].uv.y = 1 - (frame[1] + frame[3]);
	modela.vertices[3].uv.x = frame[0]; modela.vertices[3].uv.y = 1 - frame[1];

	
	//glGenBuffers(1, &modela->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, modela.vertices, GL_DYNAMIC_DRAW);
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

	set_matrix(Singleton<Camera>::GetInstance()->camera_VP);
	glUseProgram(shaders.program);
	glUniformMatrix4fv(shaders.WVP, 1, GL_FALSE, &wvpMatrix.m[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modela.iboId);

	glBindTexture(GL_TEXTURE_2D, Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].textureID);
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
	if (anim_cursor > speed) {
		curent_frame_indx = (curent_frame_indx + 1) % frames_count;
		//cout << anim_cursor << "-" << deltaTime << endl;
		anim_cursor = 0;
		//vector<float> frame = frames[curent_frame_indx];
		vector<float> frame = frames[1];
		//nomalization
		frame[0] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].width;
		frame[1] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].height;
		frame[2] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].width;
		frame[3] /= Singleton<ResourceManager>::GetInstance()->TD_Textures[texture[0]].height;

		/*model->vertices[0].uv.x = frame[0] + frame[2]; model->vertices[0].uv.y = 1 - frame[1];
		model->vertices[1].uv.x = frame[0] + frame[2]; model->vertices[1].uv.y = 1 - (frame[1] + frame[3]);
		model->vertices[2].uv.x = frame[0]; model->vertices[2].uv.y = 1 - (frame[1] + frame[3]);
		model->vertices[3].uv.x = frame[0]; model->vertices[3].uv.y = 1 - frame[1];*/

		modela.vertices[0].uv.x = (modela.vertices[0].uv.x + frame[2]); modela.vertices[0].uv.y = 1 - frame[1];
		modela.vertices[1].uv.x = (modela.vertices[1].uv.x + frame[2]); modela.vertices[1].uv.y = 1 - (frame[1] + frame[3]);
		modela.vertices[2].uv.x = (modela.vertices[2].uv.x + frame[2]); modela.vertices[2].uv.y = 1 - (frame[1] + frame[3]);
		modela.vertices[3].uv.x = (modela.vertices[3].uv.x + frame[2]); modela.vertices[3].uv.y = 1 - frame[1];

		glBindBuffer(GL_ARRAY_BUFFER, modela.vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, modela.vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Animation2D::load_element(const char* fileName){
	anim_cursor = 0;
	curent_frame_indx = 0;
	//speed = 0.05f;
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
	modela.init("../Resources/Models/animation.nfg");
	//model a = model(Singleton<ResourceManager>::GetInstance()->models[models]);
}
