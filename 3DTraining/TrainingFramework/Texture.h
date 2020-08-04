#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"

class Texture
{
public:
	Texture();
	~Texture();
	int getID();
	bool LoadTexture(char* fileName);
	static Texture* GetInstance();
	GLenum target;
	GLint tiling;
private:
	GLuint id;
	GLint width, height, bpp;
	static Texture* s_Instance;
};

