#include "stdafx.h"
#include "Camera.h"
Camera* Camera::m_Instance = nullptr;

Camera::Camera()
{
	this->position = Vector3(1, 1, -10);
	this->target = Vector3(0, 0, 0);
	cnear = 0.1f;
	cfar = 500.0f;
	cfov = 1.0;
	cspeed = 0.3f;
	horizon_rate = 50;
	norm = (position - target).Length();
	UpdateAxis();
}


Camera::~Camera()
{
}

void Camera::Normalize_v1() {
	Vector3 dist = target - position;
	position = target - dist / dist.Length() * norm;
}
void Camera::Normalize_v2() {
	Vector3 dist = target - position;
	target = position + dist / dist.Length() * norm;
}
void Camera::SetRotation(float x, float y, float z) {
	CameraRotation.x = x;
	CameraRotation.y = y;
	CameraRotation.z = z;
	//Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ;
	//RotationMatrixX.SetRotationAngleAxis(ObjectRotation.x * (3.14 / 180), 1, 0, 0);
	//RotationMatrixY.SetRotationAngleAxis(ObjectRotation.y * (3.14 / 180), 0, 1, 0);
	//RotationMatrixZ.SetRotationAngleAxis(ObjectRotation.z * (3.14 / 180), 0, 0, 1);
	//RotationMatrix = RotationMatrixY * RotationMatrixX * RotationMatrixZ;
}

void Camera::SetTranslation(float x, float y, float z) {
	CameraTranslation.x = x;
	CameraTranslation.y = y;
	CameraTranslation.z = z;
	//TranslationMatrix.SetTranslation(Vector3(-x, -y, -z));
}

void Camera::SetViewMatrix() {
	Vector3 zaxis = (position-target).Normalize();
	Vector3 up = Vector3(0, 1, 0);
	Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	ViewMatrix.m[0][0] = xaxis.x; ViewMatrix.m[0][1] = yaxis.x; ViewMatrix.m[0][2] = zaxis.x; ViewMatrix.m[0][3] = 0;
	ViewMatrix.m[1][0] = xaxis.y; ViewMatrix.m[1][1] = yaxis.y; ViewMatrix.m[1][2] = zaxis.y; ViewMatrix.m[1][3] = 0;
	ViewMatrix.m[2][0] = xaxis.z; ViewMatrix.m[2][1] = yaxis.z; ViewMatrix.m[2][2] = zaxis.z; ViewMatrix.m[2][3] = 0;
	ViewMatrix.m[3][0] = -position.Dot(xaxis); ViewMatrix.m[3][1] = -position.Dot(yaxis); ViewMatrix.m[3][2] = -position.Dot(zaxis); ViewMatrix.m[3][3] = 1;
	//Matrix RotationMatrixX, RotationMatrixY, RotationMatrixZ,TranslationMatrix;
	//RotationMatrixX.SetRotationX(-CameraRotation.x * (3.14 / 180));
	//RotationMatrixY.SetRotationY(-CameraRotation.y * (3.14 / 180));
	//RotationMatrixZ.SetRotationZ(-CameraRotation.z * (3.14 / 180));
	//TranslationMatrix.SetTranslation(Vector3(-CameraTranslation.x, -CameraTranslation.y, -CameraTranslation.z));
	//ViewMatrix = TranslationMatrix*RotationMatrixY * RotationMatrixX * RotationMatrixZ;
}
Matrix Camera::GetViewMatrix() {
	return ViewMatrix;
}

Camera* Camera::GetInstance() {
	if (!m_Instance) {
		m_Instance = new Camera;
	}
	return m_Instance;
}


Vector3 Camera::GetTranslation() {
	return CameraTranslation;
}
void Camera::SetWorldMatrix() {
	//Vector3 zaxis = (position - target).Normalize();
	//Vector3 up = Vector3(0, 1, 0);
	//Vector3 xaxis = (up.Cross(zaxis)).Normalize();
	//Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	//this->UpdateAxis();
	WorldMatrix.m[0][0] = xaxis.x; WorldMatrix.m[0][1] = xaxis.y; WorldMatrix.m[0][2] = xaxis.z; WorldMatrix.m[0][3] = 0;
	WorldMatrix.m[1][0] = yaxis.x; WorldMatrix.m[1][1] = yaxis.y; WorldMatrix.m[1][2] = yaxis.z; WorldMatrix.m[1][3] = 0;
	WorldMatrix.m[2][0] = zaxis.x; WorldMatrix.m[2][1] = zaxis.y; WorldMatrix.m[2][2] = zaxis.z; WorldMatrix.m[2][3] = 0;
	WorldMatrix.m[3][0] = position.x; WorldMatrix.m[3][1] = position.y; WorldMatrix.m[3][2] = position.z; WorldMatrix.m[3][3] = 1;

}
void Camera::MoveForward(float deltaTime) {
	//Vector3 zaxis = (position - target).Normalize();
	Vector3 deltaMove = -zaxis*deltaTime*cspeed;
	this->position += deltaMove;
	this->target += deltaMove;
}
void Camera::MoveBack(float deltaTime) {
	//Vector3 zaxis = (position - target).Normalize();
	Vector3 deltaMove = zaxis*deltaTime*cspeed;
	this->position += deltaMove;
	this->target += deltaMove;
}
void Camera::RotateLeft(float deltaTime) {
	Matrix mm;
	Vector4 localTarget = Vector4(0, 0, -(position - Camera::GetInstance()->target).Length(), 1);
	Vector4 localNewTarget = localTarget * mm.SetRotationY(deltaTime * cspeed);
	this->SetWorldMatrix();
	Vector4 worldNewTarget = localNewTarget * Camera::GetInstance()->WorldMatrix;
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	UpdateAxis();
}
void Camera::RotateRight(float deltaTime) {
	Matrix mm;
	Vector4 localTarget = Vector4(0, 0, -(position - Camera::GetInstance()->target).Length(), 1);
	Vector4 localNewTarget = localTarget * mm.SetRotationY(-deltaTime * cspeed);
	this->SetWorldMatrix();
	Vector4 worldNewTarget = localNewTarget * Camera::GetInstance()->WorldMatrix;
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	UpdateAxis();
}
void Camera::MoveUp(float deltaTime) {
	Vector3 deltaMove = yaxis*deltaTime*cspeed;
	this->position += deltaMove;
	this->target += deltaMove;
}
void Camera::MoveRight(float deltaTime) {
	Vector3 deltaMove = xaxis*deltaTime*cspeed;
	this->position += deltaMove*horizon_rate;
	Normalize_v1();
//	this->target += deltaMove;
	UpdateAxis();
}
void Camera::MoveDown(float deltaTime) {
	Vector3 deltaMove = -yaxis*deltaTime*cspeed;
	this->position += deltaMove;
	this->target += deltaMove;
}
void Camera::MoveLeft(float deltaTime) {
	Vector3 deltaMove = -xaxis*deltaTime*cspeed;
	this->position += deltaMove*horizon_rate;
	Normalize_v1();
//	this->target += deltaMove;
	UpdateAxis();
}
void Camera::UpdateAxis() {
	zaxis = (position - target).Normalize();
	Vector3 up = Vector3(0, 1, 0);
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
}
void Camera::RotateUp(float deltaTime) {
	Matrix mm;
	Vector4 localTarget = Vector4(0, 0, -(position - Camera::GetInstance()->target).Length(), 1);
	Vector4 localNewTarget = localTarget * mm.SetRotationX(-deltaTime * cspeed);
	this->SetWorldMatrix();
	Vector4 worldNewTarget = localNewTarget * Camera::GetInstance()->WorldMatrix;
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	Normalize_v2();
	UpdateAxis();
}
void Camera::RotateDown(float deltaTime) {
	Matrix mm;
	Vector4 localTarget = Vector4(0, 0, -(position - Camera::GetInstance()->target).Length(), 1);
	Vector4 localNewTarget = localTarget * mm.SetRotationX(deltaTime * cspeed);
	this->SetWorldMatrix();
	Vector4 worldNewTarget = localNewTarget * Camera::GetInstance()->WorldMatrix;
	this->target = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
	Normalize_v2();
	UpdateAxis();
}