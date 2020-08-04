#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
	void LoadFile(char* fileName);
	void Free();
	static ResourceManager* GetInstance();
	Model* GetModel();
	Texture* GetTexture();
	Shaders* GetShader();
private:
	Model* r_Model;
	Texture* r_Texture2D,*r_CubeTexture;
	Shaders *r_Shaders;
	int modelCounts, _2DTexCount, CubeTexCount, ShadersCount;
	static ResourceManager* s_Instance;
};

