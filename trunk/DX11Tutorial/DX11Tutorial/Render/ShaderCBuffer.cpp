#include "ShaderCBuffer.h"
#include "framework/SystemClass.h"
#include "Camare/ClientCamera.h"
#include "../math/Matrix4x4.h"
#include "../math/IMath.h"

CBufferManager::CBufferManager()
{
	InitConstanceMap();
}

CBufferManager::~CBufferManager()
{

}

CBufferManager& CBufferManager::Instance()
{
	static CBufferManager instance;
	return instance;
}

ShaderCBuffer* CBufferManager::get( const std::string key )
{
	CBUFFERMAP::iterator it = m_pBufferMap.find(key);
	if(it != m_pBufferMap.end())
		return it->second;
	return NULL;
}

void CBufferManager::insert( const std::string key, ShaderCBuffer* object )
{
	m_pBufferMap[key] = object;
}

void CBufferManager::InitConstanceMap()
{
	insert("WorldViewProject", new WorldViewProject());
	insert("LightData", new Light());
	insert("UIWorldViewProject", new UIWorldViewPorject());
	insert("TerrainLightData",new TerrainLightData());
}

int WorldViewProject::size()
{
	return sizeof(WorldViewProjectData);
}

bool WorldViewProject::InitBuffer( void** buffer )
{
	WorldViewProjectData* data = (WorldViewProjectData*)(*buffer);
	Matrix4x4 world = SystemClass::Instance().renderModul()->GetWorldMatrix();
	Matrix4x4 view =  ClientCamera::instance().GetViewMatrix();
	//Matrix4x4 project = SystemClass::Instance().renderModul()->GetOrthoMatrix();
	Matrix4x4 project = SystemClass::Instance().renderModul()->GetProjectionMatrix();
	Matrix4x4 newView;
	D3DXMatrixLookAtLH((D3DXMATRIX*)&newView,&D3DXVECTOR3(0,2000,-2000),&D3DXVECTOR3(0,0,0),&D3DXVECTOR3(0,1,0));

	world.Transport();
	view.Transport();
	project.Transport();
	newView.Transport();
	data->world = world;
	data->view =view;
	data->project = project;
	data->lightView = newView;
	return true;
}

WorldViewProject::WorldViewProject()
{

}

WorldViewProject::~WorldViewProject()
{

}


int Light::size()
{
	return sizeof(Light::LightData);
}

bool Light::InitBuffer( void** buffer )
{
	LightData* data = (LightData*)(*buffer);

	data->lightColor.x = 0.5f;
	data->lightColor.y = 0.5f;
	data->lightColor.z = 0.5f;
	data->lightColor.w = 0.5f;

	data->lightPostion.x = 0;

	data->lightPostion.y = 2000;

	data->lightPostion.z = -2000;

	data->lightPostion.w = 1;
	return true;
}

int UIWorldViewPorject::size()
{
	return sizeof(UIWorldViewPorjectData);
}

bool UIWorldViewPorject::InitBuffer( void** buffer )
{
	UIWorldViewPorjectData* data = (UIWorldViewPorjectData*)(*buffer);
	Matrix4x4 world =IMath::MAT4X4_IDENTITY;
	Matrix4x4 view =  ClientCamera::instance().GetUIMatrix();
	Matrix4x4 project = SystemClass::Instance().renderModul()->GetOrthoMatrix();
	//Matrix4x4 project = SystemClass::Instance().renderModul()->GetProjectionMatrix();

	world.Transport();
	view.Transport();
	project.Transport();

	data->world = world;
	data->view =view;
	data->project = project;
	return true;
}

TerrainLightData::TerrainLightData()
{

}

TerrainLightData::~TerrainLightData()
{

}

int TerrainLightData::size()
{
	return sizeof(LightBuffer);
}

bool TerrainLightData::InitBuffer( void** buffer )
{
	LightBuffer* data = (LightBuffer*)(*buffer);

	data->ambientColor = Vector4(0.2f,0.2f,0.2f, 1.0f);
	data->diffuseColor = Vector4(0.5f,0.5f,0.5f,1.0f);
	data->lightDirection = Vector3(-1.0f,-1.0f,-0.5f);
	data->padding = 0.5f;

	return true;
}