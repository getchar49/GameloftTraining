#pragma once
#include "Object.h"
#include "Camera.h"
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void LoadFile(char* fileName);
	static SceneManager* GetInstance();
	void Draw(ESContext* esContext);
private:
	//int modelID;
	int object_num;
	Object *objectList;
	//Camera* camera;
	static SceneManager* s_Instance;
	//int *textureList, *cubetextureList;
};

