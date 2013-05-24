#include "ModleLoaderSample.h"
#include "ModleLoader.h"

ModleLoaderSample::ModleLoaderSample(void)
{
}

ModleLoaderSample::~ModleLoaderSample(void)
{
}

bool ModleLoaderSample::init()
{

	//bool result = ModleLoader::Instance().loaderModel(L"../res/modle/cube.obj",&m_vertexBuffer, &m_indexBuffer);
	
	return true;
}

void ModleLoaderSample::fini()
{

}

void ModleLoaderSample::update( float det )
{

}

bool ModleLoaderSample::render()
{
	return true;
}