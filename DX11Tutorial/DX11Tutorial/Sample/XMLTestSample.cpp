#include "XMLTestSample.h"
#include "tinyxml.h"
#include "render/Effect.h"
#include "base/VertexFormat.h"
#include "base/EngineBase.h"
#include "framework/SystemClass.h"
#include "Camare/ClientCamera.h"

XMLTestSample::XMLTestSample(void)
{
}

XMLTestSample::~XMLTestSample(void)
{
}

bool XMLTestSample::init()
{
	
	XYZNUV* vertices = NULL;
	unsigned long* indices = NULL;
	bool result = true;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	// Create the vertex array.
	vertices = new XYZNUV[m_vertexCount];
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

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].normal = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertices[0].uv = D3DXVECTOR2(1.0f,0.0);

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top left.
	vertices[1].normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertices[1].uv = D3DXVECTOR2(0.0f,0.0);


	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].normal = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	vertices[2].uv = D3DXVECTOR2(1.0f,0.0);


	vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);//top l
	vertices[3].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertices[3].uv = D3DXVECTOR2(0.0f,1.0);
	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;

	m_vertexBuffer = new D3DVertexBuffer();
	if(m_vertexBuffer)
	{
		result =m_vertexBuffer->init(sizeof(XYZNUV) * m_vertexCount, (void*)vertices, sizeof(XYZNUV));
		SAFE_DELETE(vertices);
	}

	m_indexBuffer = new D3DIndexBuffer();
	if(m_indexBuffer)
	{
		result = m_indexBuffer->init(sizeof(unsigned long) * m_indexCount, (void*)indices);
		SAFE_DELETE(indices);
	}

	effect = new Effect();
	result = effect->load("../res/shader/staticModleShader.xml");
	
	m_ptexture = new Texture();
	if(m_ptexture)
	{
		result = m_ptexture->initWithFile(L"../res/texture/db_doty_shatu003.dds");
	}
	

	ClientCamera::instance().SetPosition(0.0f, 0.0f, -2.0f);
	return result;
}

void XMLTestSample::fini()
{
	
}

void XMLTestSample::update( float det )
{



}

bool XMLTestSample::render()
{

	
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

	bool  result = effect->commit();
	effect->setTexture("diffuse", m_ptexture->GetShaderResource());


	deviceContext->DrawIndexed(m_indexCount, 0, 0);

	return true;
}