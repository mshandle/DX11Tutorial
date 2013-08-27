#include "ModleLoaderSample.h"
#include "REsMrg/ModleLoader.h"
#include "../Camare/ClientCamera.h"
#include "../FrameWork/SystemClass.h"

ModleLoaderSample::ModleLoaderSample(void)
{
}

ModleLoaderSample::~ModleLoaderSample(void)
{
}

bool ModleLoaderSample::init()
{
	bool result = false;

	m_pModel = ModleLoader::Instance().loaderModel(L"../res/modle/aka_m00_wp.obj");
	
	if(NULL == m_pModel)
		return false;

	m_peffect = new Effect();
	result = m_peffect->load("../res/shader/xyznuv.xml");


	m_pTexturel = new Texture();
	if(m_pTexturel)
	{
		result = m_pTexturel->init(L"../res/texture/aka_t00_wp.dds");
	}


	ClientCamera::instance().SetPosition(-0.0f, 10.0f, -100.0f);
	//void SetRotation(float yaw, float pitch, float raw);
	ClientCamera::instance().SetRotation(0.0, 0.0f, 0.0f);

	D3DXMATRIX translate;
	D3DXMATRIX translatex;
	D3DXMatrixRotationZ(&translate,3.1415926 * 0.5);
	D3DXMatrixRotationY(&translatex,3.1415926 * 0.5);

	D3DXMATRIX& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();

	D3DXMatrixMultiply(&worldMat,&worldMat,&translate);
	D3DXMatrixMultiply(&worldMat,&worldMat,&translatex);
	return result;
}

void ModleLoaderSample::fini()
{

}

void ModleLoaderSample::update( float det )
{
	D3DXMATRIX& worldMat = SystemClass::Instance().renderModul()->GetWorldMatrix();
	D3DXMATRIX translate;
	D3DXMATRIX translateY;
	D3DXMatrixRotationX(&translate,det);
	D3DXMatrixRotationY(&translateY,det);
	//D3DXMatrixMultiply(&worldMat,&worldMat,&translate);
	D3DXMatrixMultiply(&worldMat,&worldMat,&translateY);
}

bool ModleLoaderSample::render()
{
	unsigned int offset;
	// Set vertex buffer stride and offset.
	offset = 0;
	ID3D11DeviceContext*  deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexbuffer = m_pModel->VertBuffer()->buffer();
	unsigned int stride_ = m_pModel->VertBuffer()->stride();
	deviceContext->IASetVertexBuffers(0, 1, &vertexbuffer, &stride_, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_pModel->IndexBuffer()->buffer(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	bool  result = m_peffect->commit();
	m_peffect->setTexture("diffuse", m_pTexturel->getTexture());

	unsigned int nIndexCount = m_pModel->TrisNum() * 3;

	deviceContext->DrawIndexed(nIndexCount, 0, 0);

	return true;
}