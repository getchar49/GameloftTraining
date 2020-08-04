	// TrainingFramework.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "SceneManager.h"

GLuint  colorId;
Shaders myShaders;
//int n_Indices, n_Vertices;

Object* woman;
int keys = 0;
unsigned char keyboard[32] = { 'W','S','A','D', VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,'Y','H'};

void SAFEDEL(void* t) {
	if (t != NULL) { try { delete t; } catch (...) {}; t = NULL; }
}

int Init(ESContext *esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//float wScale[] = { 0.5f,0.5f,0.5f };
	//float wRotation[] = { 60.0f,90.0f,0.0f };
	//float wTranslation[] = { 0.0f,-0.8f,0.0f};
	//float cScale[] = { 1.0f,1.0f,1.0f };
	//float cRotation[] = { 0.0f,0.0f,0.0f };
	//float cTranslation[] = { 0.0f,0.0f,0.0f};
	//woman = new Object;
	//woman->SetScale(wScale[0], wScale[1], wScale[2]);
	//woman->SetRotation(wRotation[0], wRotation[1], wRotation[2]);
	//woman->SetTranslation(wTranslation[0], wTranslation[1], wTranslation[2]);
	//Camera::GetInstance()->SetRotation(cRotation[0], cRotation[1], cRotation[2]);
	//Camera::GetInstance()->SetTranslation(cTranslation[0], cTranslation[1], cTranslation[2]);
	//Camera::GetInstance()->SetViewMatrix();
	ResourceManager::GetInstance()->LoadFile("../Resources/RM.txt");
	SceneManager::GetInstance()->LoadFile("../Resources/SM.txt");
	//woman->LoadModel("../Resources/Models/Woman1.nfg");
	//woman->BufferIBO();
	//woman->BufferVBO();

	//Texture::GetInstance()->LoadTexture("../Resources/Texture/Woman1.tga");
	
	//creation of shaders and program 
	return 0;
	//return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw(ESContext *esContext)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	

	//glUseProgram(myShaders.program);


	//glBindBuffer(GL_ARRAY_BUFFER, woman->GetVBO());
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, woman->GetIBO());
	//glBindTexture(GL_TEXTURE_2D, Texture::GetInstance()->getID());
	//glBindTexture(GL_TEXTURE_2D, Texture::GetInstance()->getID());
	SceneManager::GetInstance()->Draw(esContext);
//	glEnableVertexAttribArray(myShaders.positionAttribute);
//	glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

//	glEnableVertexAttribArray(myShaders.uvAttribute);
//	glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3) * 4);

	//glUniform1i(myShaders.uniformTexture, 0);
//	woman->SetWVP();
//	if (myShaders.uniformWVP != -1) {
//		glUniformMatrix4fv(myShaders.uniformWVP, 1, GL_FALSE, &(woman->GetWVP().m[0][0]));
//	}
	//glDrawArrays(GL_TRIANGLES, 0, 3);
//	glDrawElements(GL_TRIANGLES, woman->GetModel()->getIndices(), GL_UNSIGNED_INT, 0);

//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);

	//eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update(ESContext *esContext, float deltaTime)
{
	//float speed = 1.0;
	//Vector3 position = Camera::GetInstance()->position;
	//Vector3 target = Camera::GetInstance()->target;
	//Vector3 zaxis = (position - target).Normalize();
	//Vector3 up = Vector3(0, 1, 0);
	//Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	//Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	//Vector3 deltaMove;
	if (keys & (1 << 0)) {
		Camera::GetInstance()->MoveForward(deltaTime);
	}
	else if (keys & (1 << 1)) {
		Camera::GetInstance()->MoveBack(deltaTime);
	}
	else if (keys & (1 << 2)) {
		Camera::GetInstance()->RotateLeft(deltaTime);
	}
	else if (keys & (1 << 3)) {
		Camera::GetInstance()->RotateRight(deltaTime);
	}
	else if (keys & (1 << 4)) {
		Camera::GetInstance()->MoveUp(deltaTime);
	}
	else if (keys & (1 << 5)) {
		Camera::GetInstance()->MoveDown(deltaTime);
	}
	else if (keys & (1 << 6)) {
		Camera::GetInstance()->MoveLeft(deltaTime);
	}
	else if (keys & (1 << 7)) {
		Camera::GetInstance()->MoveRight(deltaTime);
	}
	else if (keys & (1 << 8)) {
		Camera::GetInstance()->RotateUp(deltaTime);
	}
	else if (keys & (1 << 9)) {
		Camera::GetInstance()->RotateDown(deltaTime);
	}
	//if (keys) {
	//	printf("%f %f %f\n", target.x, target.y, target.z);
	//}
	//Camera::GetInstance()->position += deltaMove;
	//Camera::GetInstance()->target += deltaMove;
	//Camera::GetInstance()->SetViewMatrix();
	//woman->SetWVP();
	keys = 0;
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (!bIsPressed) return;
	for (int i = 0; i < 32; i++) {
		if (keyboard[i] == key) {
			keys |= (1 << i);
			break;
		}
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &(Model::GetInstance()->getVBO()));
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

