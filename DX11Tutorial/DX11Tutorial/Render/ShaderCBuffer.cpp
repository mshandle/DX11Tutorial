#include "ShaderCBuffer.h"
#include "framework/SystemClass.h"
#include "Camare/ClientCamera.h"

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
}

int WorldViewProject::size()
{
	return sizeof(WorldViewProjectData);
}

bool WorldViewProject::InitBuffer( void** buffer )
{
	WorldViewProjectData* data = (WorldViewProjectData*)(*buffer);
	D3DXMATRIX world = SystemClass::Instance().renderModul()->GetWorldMatrix();
	D3DXMATRIX view =  ClientCamera::instance().GetViewMatrix();
	D3DXMATRIX project = SystemClass::Instance().renderModul()->GetProjectionMatrix();

	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&world, &world);
	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&project, &project);

	data->world = world;
	data->view =view;
	data->project = project;
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

	data->lightColor.x = 0.0f;
	data->lightColor.y = 1.0f;
	data->lightColor.z = 0.0f;
	data->lightColor.w = 1.0f;

	data->lightPostion.x = 500;

	data->lightPostion.y = 500;

	data->lightPostion.z = 100;

	data->lightPostion.w = 1;
	return true;
}