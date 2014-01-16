#include "RTTSample.h"
#include "..\UILib\UISystem.h"
#include "..\UILib\FrontLable.h"
#include "..\Camare\ClientCamera.h"
#include "..\FrameWork\SystemClass.h"
#include "..\ResMrg\ModleLoader.h"
#include "..\UILib\TextureView.h"

bool RTTSample::init()
{
	EVAUI::FrontLable* pLable = new EVAUI::FrontLable(std::string("Render To Texture Sample"), EVAUI::UISystem::instance().TopLeft());
	EVAUI::UISystem::instance().Root()->addchild(pLable);

	bool result = true;
	m_pModel = ModleLoader::Instance().loaderModel(L"../res/modle/sphere.obj");

	if(NULL == m_pModel)
		return false;

	m_peffect = new Effect();
	result = m_peffect->load("../res/shader/xyznuv.xml");


	m_pTexturel = new Texture();
	if(m_pTexturel)
	{
		result = m_pTexturel->initWithFile(L"../res/texture/bg.png");
	}


	ClientCamera::instance().SetPosition(0.0f, 10.0f, -400.0f);
	Matrix4x4 translate;

	IMath::BuildIdentityMatrix(translate);
	translate.Translate(0.0f,10.f, 0.f);

	Matrix4x4 translateZ;
	Matrix4x4 translateY;

	IMath::BuildRotateMatrixZ(translateZ, 3.1415926f * 0.5f);
	IMath::BuildRotateMatrixY(translateY, 3.1415926f * 0.5f);

	Matrix4x4& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();

	//worldMat *= translateZ;
	//worldMat *= translateY;
	//worldMat *= translate;

	EVAUI::TextureView* pBackGround = new EVAUI::TextureView();
	result = pBackGround->initTextureFile(L"../res/texture/bg.png",SystemClass::Instance().renderModul()->ViewWidth()/4.0f, SystemClass::Instance().renderModul()->ViewHeight()/4.0f);
	pBackGround->position(Vector2(EVAUI::UISystem::instance().TopLeft().x, EVAUI::UISystem::instance().TopLeft().y/2.0));
	EVAUI::UISystem::instance().Root()->addchild(pBackGround);

	DedugWindow = new EVAUI::TextureView();
	result =DedugWindow->initWithOutTexture(SystemClass::Instance().renderModul()->ViewWidth()/4.0f, SystemClass::Instance().renderModul()->ViewHeight()/4.0f);
	DedugWindow->position(Vector2(EVAUI::UISystem::instance().TopLeft().x, EVAUI::UISystem::instance().TopLeft().y/2.0f));
	EVAUI::UISystem::instance().Root()->addchild(DedugWindow);


	m_pRenderTarget = new Texture2D(SystemClass::Instance().renderModul()->GetDevice(),SystemClass::Instance().renderModul()->ViewWidth(), SystemClass::Instance().renderModul()->ViewHeight(),DXGI_FORMAT_R16G16B16A16_FLOAT);
	
	
	return result;
}

void RTTSample::fini()
{

}

void RTTSample::update( float det )
{
	Matrix4x4& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();
	Matrix4x4 rotateY;
	IMath::BuildRotateMatrixX(rotateY, det);
	worldMat *= rotateY;
}

bool RTTSample::render()
{
	ID3D11DeviceContext* deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	ID3D11DepthStencilView* pDepthStencilView = SystemClass::Instance().renderModul()->GetDepthStencilView();
	ID3D11RenderTargetView* pRenderTagerView = m_pRenderTarget->GetRenderTarget();

	deviceContext->OMSetRenderTargets(1,&pRenderTagerView,pDepthStencilView);

	Vector4 color(0.0f,0.0f,0.0f,0.0f);
	deviceContext->ClearRenderTargetView(pRenderTagerView, (float*)&color);

	// Clear the depth buffer.
	deviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_peffect->setTexture("diffuse", m_pTexturel->GetShaderResource());
	bool  result = m_peffect->commit();
	m_pModel->draw(IMath::MAT4X4_IDENTITY);

	SystemClass::Instance().renderModul()->setRenderToBackBuffer();

	deviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_pModel->draw(IMath::MAT4X4_IDENTITY);

	DedugWindow->setTexture(m_pRenderTarget);


	return true;
}