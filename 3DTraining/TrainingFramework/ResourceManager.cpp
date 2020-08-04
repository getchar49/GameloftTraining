#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::s_Instance = NULL;

ResourceManager::ResourceManager()
{
	r_Model = NULL;
	r_Texture2D = NULL;
	r_CubeTexture = NULL;
}


ResourceManager::~ResourceManager()
{
	this->Free();
}

void ResourceManager::Free() {
	if (r_Model) {
		delete[] r_Model;
		r_Model = 0;
	}
	if (r_Texture2D) {
		delete[] r_Texture2D;
		r_Texture2D = 0;
	}
	if (r_CubeTexture) {
		delete[] r_CubeTexture;
		r_CubeTexture = 0;
	}
}

void ResourceManager::LoadFile(char* fileName) {
	FILE *f = fopen(fileName, "r");
	//fscanf(f,"#Models: ");
	fscanf(f,"#Models: %d\n", &modelCounts);
	r_Model = new Model[modelCounts];
	int id;
	char tiling[50];
	char name1[50], name2[50];
	for (int i = 0; i < modelCounts; i++) {
		//fscanf(f,"ID");
		fscanf(f,"ID %d\n", &id);
		//fscanf(f,"FILE");
		fscanf(f,"FILE \"%s\n", name1);
		name1[strlen(name1) - 1] = 0;
	//	fscanf(f,"FILE %s\n",)
	//	printf("%s\n", name1);
		r_Model[id].LoadModel(name1);
	}
	int _1 = fscanf(f,"#2D Textures: %d\n",&_2DTexCount);
//	int _2 = fscanf(f,"%d", &_2DTexCount);
	r_Texture2D = new Texture[_2DTexCount];
	for (int i = 0; i < _2DTexCount; i++) {
		fscanf(f,"ID");
		fscanf(f,"%d\n", &id);
		//fscanf(f,"FILE");
		fscanf(f,"FILE \"%s\n", name1);
		name1[strlen(name1) - 1] = 0;
		//fscanf(f,"TILING");
		fscanf(f,"TILING %s\n", tiling);
		r_Texture2D[id].target = GL_TEXTURE_2D;
		if (tiling[0] == 'C') r_Texture2D[id].tiling = GL_CLAMP_TO_EDGE;
		else r_Texture2D[id].tiling = GL_REPEAT;
		r_Texture2D[id].LoadTexture(name1);
	}
	fscanf(f,"#Cube Textures:");
	fscanf(f,"%d\n", &CubeTexCount);
	r_CubeTexture = new Texture[CubeTexCount];
	for (int i = 0; i < CubeTexCount; i++) {
		fscanf(f,"ID %d\n", &id);
		fscanf(f, "\"%s\n", name1);
		name1[strlen(name1) - 1] = 0;
		fscanf(f,"TILING %s\n", tiling);
		r_CubeTexture[id].target = GL_TEXTURE_CUBE_MAP;
		if (tiling[0] == 'C') r_CubeTexture[id].tiling = GL_CLAMP_TO_EDGE;
		else r_CubeTexture[id].tiling = GL_REPEAT;
		r_CubeTexture[id].LoadTexture(name1);
	}
	fscanf(f,"#Shaders: %d\n", &ShadersCount);
	r_Shaders = new Shaders[ShadersCount];
	for (int i = 0; i < ShadersCount; i++) {
		fscanf(f,"ID %d\n", &id);
		fscanf(f, "VS \"%s\n", name1);
		name1[strlen(name1) - 1] = 0;
		fscanf(f,"FS \"%s\n", name2);
		name2[strlen(name2) - 1] = 0;
		r_Shaders[id].Init(name1, name2);
		fscanf(f,"STATES %d\n", &r_Shaders[id].StateCount);
		char state[20];
		for (int i = 0; i < r_Shaders[id].StateCount; i++) {
			fscanf(f,"STATE %s\n", state);
		}
	}
}

ResourceManager* ResourceManager::GetInstance() {
	if (!s_Instance) {
		s_Instance = new ResourceManager;
	}
	return s_Instance;
}

Model* ResourceManager::GetModel() {
	return this->r_Model;
}

Texture* ResourceManager::GetTexture() {
	return this->r_Texture2D;
}
Shaders* ResourceManager::GetShader() {
	return this->r_Shaders;
}