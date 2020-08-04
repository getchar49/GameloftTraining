#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Singleton.h"
#include "Object.h"
class Camera;

class Camera 
{
public:

	//friend class Singleton<Camera>;
	Camera();
	~Camera();
	void SetRotation(float x,float y,float z);
	void SetTranslation(float x, float y, float z);
	Matrix GetViewMatrix();
	static Camera* GetInstance();
	Vector3 GetTranslation();
	Vector3 position,target;
	float cnear, cfar, cfov, cspeed;
	void SetViewMatrix();
	Matrix WorldMatrix;
	void SetWorldMatrix();
	void MoveForward(float deltaTime);
	void MoveBack(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveUp(float);
	void MoveDown(float);
	void RotateLeft(float);
	void RotateRight(float);
	void UpdateAxis();
	void RotateUp(float);
	void RotateDown(float);
	void Normalize_v1();
	void Normalize_v2();
private:
	Vector3 CameraRotation;
	Vector3 CameraTranslation;
	Matrix ViewMatrix;
	static Camera* m_Instance;
	const float sensivity = 0.1;
	Vector3 xaxis, yaxis, zaxis;
	float horizon_rate;
	float norm;
};

