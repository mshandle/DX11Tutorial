#pragma once
#include "../math/IMath.h"

class ClientCamera
{
public:
	static ClientCamera& instance();
private:
	ClientCamera(void);
	~ClientCamera(void);
public:

	bool init();

	void SetPosition(float x, float y, float z);
	void SetRotation(float yaw, float pitch, float raw);

	Vector3 GetPosition();
	Vector3 GetRotation();

	Vector3	Direction(){return dir;}

	void update(float det);

	Matrix4x4 GetViewMatrix();


	Matrix4x4 GetUIMatrix();
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	Matrix4x4 m_viewMatrix;
	Matrix4x4 m_UiViewMatirx;

	Vector3	  dir;
};
