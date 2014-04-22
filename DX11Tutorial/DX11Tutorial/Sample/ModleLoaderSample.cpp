#include "ModleLoaderSample.h"
#include "REsMrg/ModleLoader.h"
#include "../Camare/ClientCamera.h"
#include "../FrameWork/SystemClass.h"
#include "../math/IMath.h"
#include "../UILib/TextureView.h"
#include "../UILib/UISystem.h"
#include "../ResMrg/ModleFactory.h"


using namespace EVAUI;
ModleLoaderSample::ModleLoaderSample(void)
{
}

ModleLoaderSample::~ModleLoaderSample(void)
{
}

bool ModleLoaderSample::init()
{
	bool result = true;

	m_pModel = ModleFactory::loadModleFile("../res/modle/two.3DS");
	if(m_pModel.empty())
		return false;

	m_peffect = new Effect();
	result = m_peffect->load("../res/shader/xyznuv.xml");


	m_pTexturel = new Texture();
	if(m_pTexturel)
	{
		result = m_pTexturel->initWithFile(L"../res/texture/aka_t00_wp.png");
	}

	
	ClientCamera::instance().SetPosition(0.0f, 0.0f, -300.0f);
	//ClientCamera::instance().SetRotation(0.0f,0.0,30.0);
	
	Matrix4x4& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();
	Matrix4x4 rotateZ;
	Matrix4x4 rotateX;
	IMath::BuildRotateMatrixY(rotateZ, 3.141592657 * 0.25);
	IMath::BuildRotateMatrixX(rotateX, 3.141592657*0.25);
	//worldMat*=rotateZ;
	//worldMat*=rotateX;
	pTextureView= new TextureView();
	pTextureView->position(EVAUI::UISystem::instance().TopLeft());
	if(!pTextureView->initTextureFile(L"../res/texture/bg2.png",100,768))
		return false;
	UISystem::instance().Root()->addchild(pTextureView);

	//D3DXMatrixMultiply(&worldMat,&worldMat,&translate);
	//D3DXMatrixMultiply(&worldMat,&worldMat,&translatex);
	return result;
}

void ModleLoaderSample::fini()
{

}

void ModleLoaderSample::update( float det )
{
	Matrix4x4& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();
	Matrix4x4 rotateY;
	IMath::BuildRotateMatrixY(rotateY, det);
	//worldMat *= rotateY;
}

bool ModleLoaderSample::render()
{
	m_peffect->setTexture("diffuse", m_pTexturel->GetShaderResource());
	bool  result = m_peffect->commit();
	
	for(std::vector<Model*>::iterator It = m_pModel.begin(); It != m_pModel.end(); It++)
	{
		(*It)->draw(IMath::MAT4X4_IDENTITY);
	}
	//m_pModel[0]->draw(IMath::MAT4X4_IDENTITY);
	return true;
}

