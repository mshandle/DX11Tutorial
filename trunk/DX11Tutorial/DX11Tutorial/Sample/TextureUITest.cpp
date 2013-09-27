#include "Base\EngineBase.h"
#include "TextureUITest.h"
#include "Base\VertexFormat.h"
#include "Camare\ClientCamera.h"
#include "FrameWork\SystemClass.h"
#include "UILib\TextureView.h"
#include "UILib\UISystem.h"

using namespace EVAUI;
bool TextureUITest::init()
{
	/*XYZUV* vertices = NULL;
	unsigned long* indices = NULL;

	bool result = true;
	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	vertices = new XYZUV[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	float fViewWidth = SystemClass::Instance().renderModul()->ViewWidth();

	float fViewHeight = SystemClass::Instance().renderModul()->ViewHeight();
	vertices[0].position = D3DXVECTOR3(-fViewWidth/2.0f, -fViewHeight/2.0f, 0.0f);  // Bottom left.
	
	vertices[0].uv = D3DXVECTOR2(0.0f,1.0);

	vertices[1].position = D3DXVECTOR3(-fViewWidth/2.0f, fViewHeight/2.0f, 0.0f);  // Top left.

	vertices[1].uv = D3DXVECTOR2(0.0f,0.0);


	vertices[2].position = D3DXVECTOR3(fViewWidth/2.0f, -fViewHeight/2.0f, 0.0f);  // Bottom right.
	
	vertices[2].uv = D3DXVECTOR2(1.0f,1.0);


	vertices[3].position = D3DXVECTOR3(fViewWidth/2.0f, fViewHeight/2.0f, 0.0f);//top l
	
	vertices[3].uv = D3DXVECTOR2(1.0f,0.0);
	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;


	m_pXYZUVEffect = new Effect();
	if(m_pXYZUVEffect)
	{
		m_pXYZUVEffect->load("../res/shader/xyzuv.xml");
	}

	m_ptexture = new Texture();
	if(m_ptexture)
	{
		result = m_ptexture->init(L"../res/texture/manaf_t00_wp.dds");
	}

	m_vertexBuffer = new D3DVertexBuffer();
	if(m_vertexBuffer)
	{
		result =m_vertexBuffer->init(sizeof(XYZUV) * m_vertexCount, (void*)vertices, sizeof(XYZUV));
		SAFE_DELETE(vertices);
	}

	m_indexBuffer = new D3DIndexBuffer();
	if(m_indexBuffer)
	{
		result = m_indexBuffer->init(sizeof(unsigned long) * m_indexCount, (void*)indices);
		SAFE_DELETE(indices);
	}

	ClientCamera::instance().SetPosition(0.0f, 0.0f, -1.0f);*/

	ClientCamera::instance().SetPosition(0.0f, 0.0f, -1.0f);
	TextureView* pTextureView= new TextureView();
	pTextureView->position(EVAUI::UISystem::instance().TopLeft());
	if(!pTextureView->initTextureFile(L"../res/texture/bg2.png",100,768))
		return false;
	UISystem::instance().Root()->addchild(pTextureView);
	return true;
}

void TextureUITest::fini()
{

}

void TextureUITest::update( float det )
{

}

bool TextureUITest::render()
{
	/*
	//return true;
	unsigned int offset;
	// Set vertex buffer stride and offset.
	offset = 0;
	ID3D11DeviceContext*  deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexbuffer = m_vertexBuffer->buffer();
	unsigned int stride_ = m_vertexBuffer->stride();
	deviceContext->IASetVertexBuffers(0, 1, &vertexbuffer, &stride_, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer->buffer(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pXYZUVEffect->setTexture("diffuse", m_ptexture->getTexture());
	bool  result = m_pXYZUVEffect->commit();
	

	SystemClass::Instance().renderModul()->TurnOffDepth();
	deviceContext->DrawIndexed(m_indexCount, 0, 0);
	SystemClass::Instance().renderModul()->TurnOnDepth();*/
	return true;
}