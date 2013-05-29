#include "ShaderCBuffer.h"
#include "SystemClass.h"
#include "ClientCamera.h"

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
}