#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::s_Instance = NULL;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::LoadFile(char* fileName) {
	FILE* f = fopen(fileName,"r");
	fscanf(f, "#Objects: %d\n", &object_num);
	objectList = new Object[object_num];
	int id, textureID;
	for (int i = 0; i < object_num; i++) {
		fscanf(f,"ID %d\n", &id);
		fscanf(f, "MODEL %d\n", &(objectList[id].modelID));
		objectList[id].BufferModel();
		fscanf(f, "TEXTURES %d\n", &(objectList[id].textures_num));
		objectList[id].textureList = new int[objectList[id].textures_num];
		for (int j = 0; j < objectList[id].textures_num; j++) {
			fscanf(f, "TEXTURE %d\n", &textureID);
			objectList[id].textureList[j] = textureID;
		}
		fscanf(f, "CUBETEXTURES %d\n", &(objectList[id].cubetextures_num));

		for (int j = 0; j < objectList[id].cubetextures_num; j++) {
			fscanf(f, "CUBETEX %d\n", &textureID);
			objectList[id].cubetextureList[j] = textureID;
		}
		fscanf(f, "SHADER %d\n", &(objectList[id].shaderID));
		Vector3 pos;
		fscanf(f, "POSITION %f %f %f\n", &(pos.x), &(pos.y), &(pos.z));
		//pos.Normalize();
		objectList[id].SetTranslation(pos);
		fscanf(f, "ROTATION %f %f %f\n", &(pos.x), &(pos.y), &(pos.z));
		objectList[id].SetRotation(pos);
		fscanf(f, "SCALE %f %f %f\n", &(pos.x), &(pos.y), &(pos.z));
		objectList[i].SetScale(pos);
	}
	fscanf(f,"#CAMERA\n");
	fscanf(f, "NEAR %f\n", &((Camera::GetInstance())->cnear));
	fscanf(f, "FAR %f\n", &((Camera::GetInstance())->cfar));
	fscanf(f, "FOV %f\n", &((Camera::GetInstance())->cfov));
	fscanf(f, "SPEED %f\n", &((Camera::GetInstance())->cspeed));
}

SceneManager* SceneManager::GetInstance() {
	if (!s_Instance) {
		s_Instance = new SceneManager;
	}
	return s_Instance;
}
void SceneManager::Draw(ESContext* esContext) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < object_num; i++) {
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int shaderID = objectList[i].shaderID;
		Shaders curShader = ResourceManager::GetInstance()->GetShader()[shaderID];
		glUseProgram(curShader.program);
		glBindBuffer(GL_ARRAY_BUFFER, objectList[i].GetVBO());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectList[i].GetIBO());
		for (int j = 0; j < objectList[i].textures_num; j++) {
			int id = objectList[i].textureList[j];
			GLuint id2 = ResourceManager::GetInstance()->GetTexture()[id].getID();
			glBindTexture(GL_TEXTURE_2D, id2);
		}
		glEnableVertexAttribArray(curShader.positionAttribute);
		glVertexAttribPointer(curShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(curShader.uvAttribute);
		glVertexAttribPointer(curShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) * 4);
		glUniform1i(curShader.uniformTexture, 0);
		objectList[i].SetWVP();
		if (curShader.uniformWVP != -1) {
			glUniformMatrix4fv(curShader.uniformWVP, 1, GL_FALSE, &(objectList[i].GetWVP().m[0][0]));
		}
		int modelID = objectList[i].modelID;
		Model* t = ResourceManager::GetInstance()->GetModel() + modelID;
		glDrawElements(GL_TRIANGLES, t->getIndices(), GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		//eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
	}
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}