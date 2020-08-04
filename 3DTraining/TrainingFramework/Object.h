#pragma once
#include "Model.h"
#include "Texture.h"
#include "Globals.h"
#include "ResourceManager.h"
class Object;

class Object
{
public:
	Object();
	~Object();
	Matrix& GetWVP();
	static Object* GetInstance();
	//bool LoadModel(char* fileName);
	bool BufferModel();
	bool LoadTexture();
	//void BufferIBO();
	//void BufferVBO();
	//Model* GetModel();
	GLuint& GetIBO();
	GLuint& GetVBO();
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 t);
	void SetScale(float x, float y, float z);
	void SetScale(Vector3 t);
	void SetTranslation(float x, float y, float z);
	void SetTranslation(Vector3 t);
	void SetViewMatrix();
	void SetWVP();
	void SetWorldMatrix();
	Matrix GetWorldMatrix();
	Vector3 GetObjectTranslation();
	int *textureList, *cubetextureList;
	int modelID;
	int textures_num, cubetextures_num;
	int shaderID;
	Vector3 ObjectTranslation;
	Vector3 ObjectRotation;
	Vector3 ObjectScale;
private:
	Matrix WorldMatrix, ViewMatrix, ProjectionMatrix;
	Matrix WVP;
	//Model* m;
	//Texture* t;
	static Object* s_Instance;
};

