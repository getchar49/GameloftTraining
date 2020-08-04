#include "stdafx.h"
#include "Object.h"
#include "Camera.h"
Object* Object::s_Instance = NULL;

Object::Object()
{
	ObjectRotation.x = 0;
	ObjectRotation.y = 0;
	ObjectRotation.z = 0;
//	ScaleMatrix.SetScale(Vector3(1.0f, 1.0f, 1.0f));
//	Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ;
//	RotationMatrixX.SetRotationAngleAxis(ObjectRotation.x * (3.14 / 180), 1, 0, 0);
//	RotationMatrixY.SetRotationAngleAxis(ObjectRotation.y * (3.14 / 180), 0, 1, 0);
//	RotationMatrixZ.SetRotationAngleAxis(ObjectRotation.z * (3.14 / 180), 0, 0, 1);
//	RotationMatrix = RotationMatrixZ * RotationMatrixX * RotationMatrixY;

//	TranslationMatrix.SetTranslation(Vector3(0.0f, -1.0f, 0.0f));

}


Object::~Object()
{
	
}

void Object::SetRotation(float x, float y, float z) {
	ObjectRotation.x = x;
	ObjectRotation.y = y;
	ObjectRotation.z = z;
//	Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ;
//	RotationMatrixX.SetRotationAngleAxis(ObjectRotation.x * (3.14 / 180), 1, 0, 0);
//	RotationMatrixY.SetRotationAngleAxis(ObjectRotation.y * (3.14 / 180), 0, 1, 0);
//	RotationMatrixZ.SetRotationAngleAxis(ObjectRotation.z * (3.14 / 180), 0, 0, 1);
//	RotationMatrix = RotationMatrixZ * RotationMatrixX * RotationMatrixY;
}

void Object::SetScale(float x,float y,float z) {
	ObjectScale = Vector3(x,y,z);
}
void Object::SetTranslation(float x, float y, float z) {
	ObjectTranslation = Vector3(x,y,z);
}

void Object::SetWorldMatrix() {
	Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ,ScaleMatrix,TranslationMatrix;
	RotationMatrixX.SetRotationX(ObjectRotation.x * (3.14 / 180));
	RotationMatrixY.SetRotationY(ObjectRotation.y * (3.14 / 180));
	RotationMatrixZ.SetRotationZ(ObjectRotation.z * (3.14 / 180));
	ScaleMatrix.SetScale(ObjectScale);
	TranslationMatrix.SetTranslation(ObjectTranslation);
	WorldMatrix = ScaleMatrix*RotationMatrixZ * RotationMatrixX * RotationMatrixY*TranslationMatrix;
	//return WorldMatrix;
}
Matrix Object::GetWorldMatrix() {
	return WorldMatrix;
}

void Object::SetWVP() {
	this->SetWorldMatrix();
	this->SetViewMatrix();
	//ProjectionMatrix.SetIdentity();
	ProjectionMatrix.SetPerspective(0.5f,1.0f,0.5f,100.f);
	WVP = WorldMatrix*ViewMatrix*ProjectionMatrix;
}
Matrix& Object::GetWVP() {
	return WVP;
}
Object* Object::GetInstance() {
	if (!s_Instance) {
		s_Instance = new Object;
	}
	return s_Instance;
}

/*bool Object::LoadModel(char* fileName) {
	if (!this->m) this->m = new Model;
	return (this->m->LoadModel(fileName));
}

bool Object::LoadTexture(char* fileName) {
	if (!this->t) this->t = new Texture;
	return (this->t->LoadTexture(fileName));
}
void Object::BufferIBO() {
	this->m->BufferIBO();
}
void Object::BufferVBO() {
	this->m->BufferVBO();
}*/
bool Object::BufferModel() {
	Model* t = &ResourceManager::GetInstance()->GetModel()[modelID];
	t->BufferIBO();
	t->BufferVBO();
	glEnable(GL_DEPTH_TEST);
	return true;
}

bool Object::LoadTexture() {
	//Texture* t = ResourceManager::GetInstance()->
	return true;
}

/*Model* Object::GetModel() {
		return this->m;
}
*/
GLuint& Object::GetIBO() {
	Model* t = ResourceManager::GetInstance()->GetModel() + this->modelID;
	return t->getIBO();
}
GLuint& Object::GetVBO() {
	Model* t = ResourceManager::GetInstance()->GetModel() + this->modelID;
	return t->getVBO();
}
void Object::SetViewMatrix() {
	Camera::GetInstance()->SetViewMatrix();
	this->ViewMatrix = Camera::GetInstance()->GetViewMatrix();
}
//Matrix Object::GetTranslationMatrix() {
//	return this->TranslationMatrix;
//}
//Matrix Object::GetRotationMatrix() {
//	return this->RotationMatrix;
//}
Vector3 Object::GetObjectTranslation() {
	return this->ObjectTranslation;
}
void Object::SetTranslation(Vector3 t) {
	this->ObjectTranslation = t;
}
void Object::SetRotation(Vector3 t) {
	this->ObjectRotation = t;
}
void Object::SetScale(Vector3 t) {
	this->ObjectScale = t;
}