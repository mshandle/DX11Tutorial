#include "ModleFactory.h"
#include "..\Render\Model\model.h"
#include <string>
#include "ModleLoader.h"
#include "ModleLoader3ds.h"

std::vector<Model*> ModleFactory::loadModleFile( const std::string& fileanme )
{

	size_t lastchar = fileanme.find_last_of('.');
	
	std::string fileExt = fileanme.substr(lastchar+1, fileanme.size() - lastchar);
	
	if(fileExt == std::string("obj"))
	{
		return loadObjModle(fileanme);
	}
	else if(fileExt.compare("3ds") || fileExt.compare("3DS"))
	{
		return load3dsModle(fileanme);
	}

	 std::vector<Model*> emp;
	 return emp;
}

std::vector<Model*> ModleFactory::loadObjModle( const std::string& file )
{
	std::vector<Model*> result;
	 result.push_back(ModleLoader::Instance().loaderModel(file));
	 return result;
}

std::vector<Model*> ModleFactory::load3dsModle( const std::string& file )
{
	Load3ds* newloader = new Load3ds();
	newloader->loadFile(file.c_str());
	
	std::vector<Model*> resultModles;
	
	std::vector<ObjectData>& objects = newloader->GetObject();

	for(std::vector<ObjectData>::iterator It = objects.begin(); It != objects.end(); It++)
	{
		bool result = true;
		D3DVertexBuffer* m_vertexBuffer = new D3DVertexBuffer();
		if(m_vertexBuffer)
		{
			result =m_vertexBuffer->init(sizeof(XYZNUV) * It->VerCount, (void*)It->verData,sizeof(XYZNUV));
			//SAFE_DELETE(pVertBuff);
		}

		D3DIndexBuffer* m_indexBuffer = new D3DIndexBuffer();
		if(m_indexBuffer)
		{
			result = m_indexBuffer->init(sizeof(unsigned long) * It->IndexCount, (void*)It->indexData);
			//SAFE_DELETE(indices);
		}

		Model* pModle = new Model(m_vertexBuffer, m_indexBuffer,It->IndexCount);
		
		resultModles.push_back(pModle);
	}

	delete newloader;

	return resultModles;

}