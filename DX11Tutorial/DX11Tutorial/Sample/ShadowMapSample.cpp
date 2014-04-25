#include "ShadowMapSample.h"
#include "..\UILib\UISystem.h"
#include "..\UILib\FrontLable.h"
#include "..\Camare\ClientCamera.h"
#include "..\FrameWork\SystemClass.h"
#include "..\ResMrg\ModleLoader.h"
#include "..\UILib\TextureView.h"
#include "..\ResMrg\ModleFactory.h"

bool ShadowMapSample::init()
{
	EVAUI::FrontLable* pLable = new EVAUI::FrontLable(std::string("ShadowMap Sample"), EVAUI::UISystem::instance().TopLeft());
	EVAUI::UISystem::instance().Root()->addchild(pLable);

	bool result = true;
	m_pModel = ModleFactory::loadModleFile("../res/modle/two_.3DS");

	if(m_pModel.empty())
		return false;

	m_peffect = new Effect();
	result = m_peffect->load("../res/shader/xyznuvcastShadow.xml");

	m_pDepthMapEffect = new Effect();
	result = m_pDepthMapEffect->load("../res/shader/depthamp.xml");

	m_pTexturel = new Texture();
	if(m_pTexturel)
	{
		result = m_pTexturel->initWithFile(L"../res/texture/db_doty_shatu003.dds");
	}
	ClientCamera::instance().SetPosition(-400.0f, 400.0f, -2500.0f);
	Matrix4x4 translate;

	IMath::BuildIdentityMatrix(translate);
	translate.Scale(20,20,20);
	Matrix4x4& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();
	
	worldMat *= translate;

	EVAUI::TextureView* pBackGround = new EVAUI::TextureView();
	result = pBackGround->initTextureFile(L"../res/texture/bg.png",SystemClass::Instance().renderModul()->ViewWidth()/4.0f, SystemClass::Instance().renderModul()->ViewHeight()/4.0f);
	pBackGround->position(Vector2(EVAUI::UISystem::instance().TopLeft().x, EVAUI::UISystem::instance().TopLeft().y/2.0));
	EVAUI::UISystem::instance().Root()->addchild(pBackGround);

	DedugWindow = new EVAUI::TextureView();
	result =DedugWindow->initWithOutTexture(SystemClass::Instance().renderModul()->ViewWidth()/4.0f, SystemClass::Instance().renderModul()->ViewHeight()/4.0f);
	DedugWindow->position(Vector2(EVAUI::UISystem::instance().TopLeft().x, EVAUI::UISystem::instance().TopLeft().y/2.0f));
	EVAUI::UISystem::instance().Root()->addchild(DedugWindow);


	m_pRenderTarget = new Texture2D(SystemClass::Instance().renderModul()->GetDevice(),SystemClass::Instance().renderModul()->ViewWidth(), SystemClass::Instance().renderModul()->ViewHeight(),DXGI_FORMAT_R32G32B32A32_FLOAT);


	return result;
}

void ShadowMapSample::fini()
{

}

void ShadowMapSample::update( float det )
{
	Matrix4x4& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();
	Matrix4x4 rotateY;
	IMath::BuildRotateMatrixY(rotateY, det);
	//worldMat *= rotateY;
}

bool ShadowMapSample::render()
{
	ID3D11DeviceContext* deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	ID3D11DepthStencilView* pDepthStencilView = SystemClass::Instance().renderModul()->GetDepthStencilView();
	ID3D11RenderTargetView* pRenderTagerView = m_pRenderTarget->GetRenderTarget();

	//draw depth map
	deviceContext->OMSetRenderTargets(1,&pRenderTagerView,pDepthStencilView);
	Vector4 color(0.0f,0.0f,0.0f,0.0f);
	deviceContext->ClearRenderTargetView(pRenderTagerView, (float*)&color);
	// Clear the depth buffer.
	deviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//build new view matrix with Light Position and direction

	Matrix4x4 oldView = ClientCamera::instance().GetViewMatrix();

	Matrix4x4 newView;
	D3DXMatrixLookAtLH((D3DXMATRIX*)&newView,&D3DXVECTOR3(0,2000,-2000),&D3DXVECTOR3(0,0,0),&D3DXVECTOR3(0,1,0));

	ClientCamera::instance().SetViewMatrix(newView);

	bool result = false;
	result = m_pDepthMapEffect->commit();

	for(std::vector<Model*>::iterator It = m_pModel.begin(); It != m_pModel.end(); It++)
	{
		(*It)->draw(IMath::MAT4X4_IDENTITY);
	}
	//normal draw

	ClientCamera::instance().SetViewMatrix(oldView);
	SystemClass::Instance().renderModul()->setRenderToBackBuffer();
	
	deviceContext->ClearDepthStencilView(pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_peffect->setTexture("Depth", m_pRenderTarget->GetShaderResource());//set depth map
	m_peffect->setTexture("diffuse", m_pTexturel->GetShaderResource());//set depth map
	result = m_peffect->commit();
	for(std::vector<Model*>::iterator It = m_pModel.begin(); It != m_pModel.end(); It++)
	{
		(*It)->draw(IMath::MAT4X4_IDENTITY);
	}
	
	static bool saveToTexture = false;
	if(!saveToTexture)
	{
		ID3D11ShaderResourceView* resourceView = m_pRenderTarget->GetShaderResource();
		ID3D11Resource* resl = NULL;
		resourceView->GetResource(&resl);
		D3DX11SaveTextureToFile(deviceContext,resl,D3DX11_IFF_PNG,L"D:/evad11engine/DX11Tutorial/Depth.png");
		DedugWindow->setTexture(m_pRenderTarget);

		saveToTexture = true;
	}
	


	return true;
}