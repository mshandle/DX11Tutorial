#include "ClientCamera.h"
#include "..\Input\InputClass.h"

ClientCamera::ClientCamera(void)
{
	m_positionX = 0.f;
	m_positionY = 0.f;
	m_positionZ = 0.f;
	
	m_rotationX = 0.f;
	m_rotationY = 0.f;
	m_rotationZ = 0.f;
}

ClientCamera::~ClientCamera(void)
{
}

ClientCamera& ClientCamera::instance()
{
	static ClientCamera instance;
	return instance;
}

bool ClientCamera::init()
{
	dir = Vector3(0.0f,0.0f,1.0f);

	D3DXMatrixLookAtLH((D3DXMATRIX*)&m_UiViewMatirx,&D3DXVECTOR3(0.0f,0.0,-1.0),&D3DXVECTOR3(0.0,0.0,0.0), &D3DXVECTOR3(0.0,1.0,0.0));
	return true;
}

void ClientCamera::SetPosition( float x, float y, float z )
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
}

void ClientCamera::SetRotation( float yaw, float pitch, float raw )
{
	
	m_rotationX = yaw;
	m_rotationY = pitch;
	m_rotationZ = raw;
}

Vector3 ClientCamera::GetPosition()
{
	return Vector3(m_positionX, m_positionY, m_positionZ);
}

Vector3 ClientCamera::GetRotation()
{
	return Vector3(m_rotationX, m_rotationY, m_rotationZ);
}

void ClientCamera::update( float det )
{
	Vector3 up, position, lookAt;
	float yaw, pitch, roll;
	Matrix4x4 rotationMatrix;

	if(InputDevice::Instance()->IsKeyDown(87))
	{
		m_positionZ+=2;
	}
	if(InputDevice::Instance()->IsKeyDown(83))
	{
		m_positionZ-=2;
	}

	if(InputDevice::Instance()->IsKeyDown(68))
	{
		m_positionX+=2;
	}

	if(InputDevice::Instance()->IsKeyDown(65))
	{
		m_positionX-=2;
	}

	if(InputDevice::Instance()->IsKeyDown(81))
	{
		m_positionY-=2;
	}
	if(InputDevice::Instance()->IsKeyDown(69))
	{
		m_positionY+=2;
	}

	if(InputDevice::Instance()->IsKeyDown(102))
	{
		dir.x += 0.02f;
	}

	if(InputDevice::Instance()->IsKeyDown(100))
	{
		dir.x -= 0.02f;
	}

	if(InputDevice::Instance()->IsKeyDown(104))
	{
		dir. y+= 0.02f;
	}
	if(InputDevice::Instance()->IsKeyDown(98))
	{
		dir. y-= 0.02f;
	}
	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.


	IMath::BuildYawPitchRoll(rotationMatrix, yaw, pitch, roll);


	//IMath::BuildRotateMatrix()

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord((D3DXVECTOR3*)&lookAt, (D3DXVECTOR3*)&lookAt, (D3DXMATRIX*)&rotationMatrix);
	D3DXVec3TransformCoord((D3DXVECTOR3*)&up, (D3DXVECTOR3*)&up, (D3DXMATRIX*)&rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.

	Vector3  newlookat = position + dir;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH((D3DXMATRIX*)&m_viewMatrix, (D3DXVECTOR3*)&position,(D3DXVECTOR3*) &newlookat, (D3DXVECTOR3*)&up);

	return;
}

Matrix4x4 ClientCamera::GetViewMatrix()
{
	return m_viewMatrix;
}

Matrix4x4 ClientCamera::GetUIMatrix()
{
	return m_UiViewMatirx;
}

void ClientCamera::SetViewMatrix( const Matrix4x4& mat )
{
	m_viewMatrix = mat;
}