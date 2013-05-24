#include "ShaderCBuffer.h"
#include "SystemClass.h"
#include "ClientCamera.h"

WorldViewProject WorldViewProject::instance;
int WorldViewProject::size()
{
	return sizeof(WorldViewProjectData);
}

bool WorldViewProject::InitBuffer( void** buffer )
{
	WorldViewProjectData* data = (WorldViewProjectData*)(*buffer);
	data->world = SystemClass::Instance().renderModul()->GetWorldMatrix();
	data->view = ClientCamera::instance().GetViewMatrix();
	data->project = SystemClass::Instance().renderModul()->GetProjectionMatrix();
	return true;
}

WorldViewProject::WorldViewProject()
{
	CBufferManager::Instance().insert("WorldViewProject", this);
}

WorldViewProject::~WorldViewProject()
{

}

CBufferManager::CBufferManager()
{

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
	//m_pBufferMap.find(key)-
	CBUFFERMAP::iterator it = m_pBufferMap.find(key);
	if(it != m_pBufferMap.end())
		return it->second;
	return NULL;
}

void CBufferManager::insert( const std::string key, ShaderCBuffer* object )
{
	m_pBufferMap[key] = object;
}