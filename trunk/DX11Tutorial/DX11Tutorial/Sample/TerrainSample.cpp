#include "TerrainSample.h"
#include "..\UILib\FrontLable.h"
#include "..\UILib\UISystem.h"
#include "..\Base\VertexFormat.h"
#include "..\Base\EngineBase.h"
#include "..\FrameWork\SystemClass.h"
#include "..\Camare\ClientCamera.h"
#include "..\Render\Terrain\TerrainBaseBlock.h"

TerrainSample::TerrainSample()
{

}

TerrainSample::~TerrainSample()
{

}

bool TerrainSample::init()
{

	Vector2 position = EVAUI::UISystem::instance().TopLeft();
	position.x +=20;
	position.y -=20;
	EVAUI::FrontLable* lable = new EVAUI::FrontLable(std::string("TerrainSample"),position);

	EVAUI::UISystem::instance().Root()->addchild(lable);

	Effect* peff = new Effect();
	peff->load("../res/shader/xyzn.xml");

	pBlock = new TerrainBaseBlock();
	pBlock->init("../res/texture/heightmap01.bmp");

	ClientCamera::instance().SetPosition(100.0f, 50.0f, -400.0f);

	return true;
}

void TerrainSample::fini()
{

}

void TerrainSample::update( float det )
{

}

bool TerrainSample::render()
{
	pBlock->draw(IMath::MAT4X4_IDENTITY);

	return true;
}