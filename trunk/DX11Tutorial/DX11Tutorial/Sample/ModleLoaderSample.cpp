#include "ModleLoaderSample.h"
#include "REsMrg/ModleLoader.h"
#include "../Camare/ClientCamera.h"
#include "../FrameWork/SystemClass.h"
#include "../math/IMath.h"
#include "../UILib/TextureView.h"
#include "../UILib/UISystem.h"


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
	//ClientCamera::instance().SetPosition(0.0f, 0.0f, -1.0f);
	m_pModel = ModleLoader::Instance().loaderModel(L"../res/modle/yadianna.obj");
	
	if(NULL == m_pModel)
		return false;

	m_peffect = new Effect();
	result = m_peffect->load("../res/shader/xyznuv.xml");


	m_pTexturel = new Texture();
	if(m_pTexturel)
	{
		result = m_pTexturel->initWithFile(L"../res/texture/db_doty_shatu003.dds");
	}

	
	ClientCamera::instance().SetPosition(0.0f, 100, -600.0f);
	Matrix4x4 translate;

	IMath::BuildIdentityMatrix(translate);
	translate.Translate(0.0f,10.f, 0.f);
	
	Matrix4x4 translateZ;
	Matrix4x4 translateY;

	IMath::BuildRotateMatrixZ(translateZ, 3.1415926f * 0.5f);
	IMath::BuildRotateMatrixY(translateY, 0.5);

	Matrix4x4& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();

	//worldMat *= translateZ;
	//worldMat *= translateY;
	//worldMat *= translate;

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
	worldMat *= rotateY;
}

bool ModleLoaderSample::render()
{
	m_peffect->setTexture("diffuse", m_pTexturel->GetShaderResource());
	bool  result = m_peffect->commit();
	m_pModel->draw(IMath::MAT4X4_IDENTITY);
	return true;
}

