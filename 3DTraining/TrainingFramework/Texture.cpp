#include "stdafx.h"
#include "Texture.h"

Texture* Texture::s_Instance = NULL;

Texture::Texture()
{
//	glGenTextures(1, &id);
//	glBindTexture(GL_TEXTURE_2D, id);
//	glActiveTexture(0);
//	glBindTexture(GL_TEXTURE_2D, 0);
	target = GL_TEXTURE_2D;
	tiling = GL_REPEAT;
}


Texture::~Texture()
{
}

int Texture::getID() {
	return this->id;
}

bool Texture::LoadTexture(char* fileName) {
	glGenTextures(1, &(this->id));
	glBindTexture(GL_TEXTURE_2D, this->id);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//GLint width, height, iComponent;
	char *imageData = LoadTGA(fileName, &width, &height, &bpp);
	if (!imageData) return false;
	if (bpp == 24) {
		glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	}
	else {
		glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
	glTexParameteri(target, GL_TEXTURE_WRAP_S, tiling);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, tiling);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glGenerateMipmap(target);
	glActiveTexture(0);
	glBindTexture(target, 0);
	if (imageData) {
		delete imageData;
		imageData = NULL;
	}
	return true;
}

Texture* Texture::GetInstance() {
	if (!s_Instance) {
		s_Instance = new Texture;
	}
	return s_Instance;
}
