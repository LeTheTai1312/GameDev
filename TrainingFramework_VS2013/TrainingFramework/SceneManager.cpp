#include "stdafx.h"
#include "SceneManager.h"
#include "Singleton.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::loadObjects(char *l) {
	int ob, objectID, modelID, textureID, cubeTextureID, shaderID;
	FILE *file;
	file = fopen(l, "r");
	fscanf(file, "#Objects: %d\n", &objectNum);
	objects = new Objects[objectNum];
	for(int i = 0; i < objectNum; i++){
		fscanf(file, "ID %d\n", &objectID);
		fscanf(file, "MODEL %d\n", &modelID);
		objects[objectID].models = modelID;

		fscanf(file, "TEXTURES %d\n", &textureNum);
		objects[objectID].texture = new int[textureNum];
		objects[objectID].textureNum = textureNum;
		for (int j = 0; j < textureNum; j++) {
			fscanf(file, "TEXTURE %d\n", &textureID);
			objects[objectID].texture[j] = textureID;
		}

		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
		objects[objectID].cubeTexture = new int[cubeTextureNum];
		objects[objectID].cubeTextureNum = cubeTextureNum;
		for (int j = 0; j < cubeTextureNum; j++) {
			fscanf(file, "CUBETEX %d\n", &cubeTextureID);	
			objects[objectID].cubeTexture[j] = cubeTextureID;
		}

		fscanf(file, "SHADER %d\n", &shaderID);
		objects[objectID].shaders = Singleton<ResourceManager>::GetInstance()->shader[shaderID];
		int a = objects[objectID].textureNum;
		objects[objectID].shaders.m_texture = new int[a];
		fscanf(file, "POSITION %f, %f, %f\n", &objects[objectID].txw, &objects[objectID].tyw, &objects[objectID].tzw);
		fscanf(file, "ROTATION %f, %f, %f\n", &objects[objectID].rxw, &objects[objectID].ryw, &objects[objectID].rzw);
		fscanf(file, "SCALE %f, %f, %f\n", &objects[objectID].sxw, &objects[objectID].syw, &objects[objectID].szw);
	}

	fscanf(file, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f", &camera.nearPlane, &camera.farPlane, &camera.fov, &camera.speed);
	fclose(file);

}

void SceneManager::draw() {
	camera.set_CamVP();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < objectNum; i++) {
		
		objects[i].set_matrix(camera.camera_VP);
		glUseProgram(objects[i].shaders.program);
		glUniformMatrix4fv(objects[i].shaders.WVP, 1, GL_FALSE, &objects[i].wvpMatrix.m[0][0]);

		glBindBuffer(GL_ARRAY_BUFFER, Singleton<ResourceManager>::GetInstance()->models[objects[i].models].vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Singleton<ResourceManager>::GetInstance()->models[objects[i].models].iboId);

		//glBindTexture(GL_TEXTURE_2D, RsMnger.TD_Textures[objects[i].texture[0]].textureID);
		//int iTextureLoc = glGetUniformLocation(objects[i].shaders.program, "u_texture");
		//glUniform1i(iTextureLoc, 0);
		for (int j = 0; j < objects[i].textureNum; j++) {
			glActiveTexture(GL_TEXTURE0 + j);
			glBindTexture(GL_TEXTURE_2D, Singleton<ResourceManager>::GetInstance()->TD_Textures[objects[i].texture[j]].textureID);
			glUniform1i(glGetUniformLocation(objects[i].shaders.program, "u_texture"), j);
		}

		/*if (objects[i].textureNum > 1) {
			//for (int j = 0; j < objects[i].textureNum; j++) {
				glUniform1i(glGetUniformLocation(objects[i].shaders.program, "u_texture0"), 0);
				glUniform1i(glGetUniformLocation(objects[i].shaders.program, "u_texture0"), 1);
				glUniform1i(glGetUniformLocation(objects[i].shaders.program, "u_texture2"), 2);
				glUniform1i(glGetUniformLocation(objects[i].shaders.program, "u_texture3"), 3);
				//glUniform1i(glGetUniformLocation(objects[i].shaders.program, "u_texture3"), 1);
				glActiveTexture(GL_TEXTURE1);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, RsMnger.TD_Textures[4].textureID);
				glActiveTexture(GL_TEXTURE2);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, RsMnger.TD_Textures[5].textureID);
				glActiveTexture(GL_TEXTURE2);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, RsMnger.TD_Textures[5].textureID);
				glActiveTexture(GL_TEXTURE3);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, RsMnger.TD_Textures[5].textureID);
			//}
		}
		else {
			glBindTexture(GL_TEXTURE_2D, RsMnger.TD_Textures[0].textureID);
			int iTextureLoc = glGetUniformLocation(objects[i].shaders.program, "u_texture");
			glUniform1i(iTextureLoc, 0);
		}*/

		glBindTexture(GL_TEXTURE_CUBE_MAP, Singleton<ResourceManager>::GetInstance()->cube_Textures[0].cubeTextureID);
		int cTextureLoc = glGetUniformLocation(objects[i].shaders.program, "u_samplerCubeMap");
		glUniform1i(cTextureLoc, 0);

		if (objects[i].shaders.positionAttribute != -1)
		{
			glEnableVertexAttribArray(objects[i].shaders.positionAttribute);
			glVertexAttribPointer(objects[i].shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}
		if (objects[i].shaders.uvAttribute != -1)
		{
			glEnableVertexAttribArray(objects[i].shaders.uvAttribute);
			glVertexAttribPointer(objects[i].shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)
				+ sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
		}
		
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES, Singleton<ResourceManager>::GetInstance()->models[objects[i].models].num_indice, GL_UNSIGNED_INT, 0);
		glDepthMask(GL_TRUE);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneManager::free() {
}
