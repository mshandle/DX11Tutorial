#pragma once

#include <d3dx10math.h>

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

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void update(float det);

	D3DXMATRIX GetViewMatrix();
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
};
