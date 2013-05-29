#include "XMLTestSample.h"
#include "tinyxml.h"
#include "Effect.h"
#include "VertexFormat.h"
#include "EngineBase.h"
#include "SystemClass.h"
#include "ClientCamera.h"
XMLTestSample::XMLTestSample(void)
{
}

XMLTestSample::~XMLTestSample(void)
{
}

bool XMLTestSample::init()
{
	
	XYZRGBA* vertices = NULL;
	unsigned long* indices = NULL;
	bool result = true;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	// Create the vertex array.
	vertices = new XYZRGBA[m_vertexCount];
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
	vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].color = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertices[3].color = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0);
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
		result =m_vertexBuffer->init(sizeof(XYZRGBA) * m_vertexCount, (void*)vertices);
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

	unsigned int stride;
	unsigned int offset;
	// Set vertex buffer stride and offset.
	stride = sizeof(XYZRGBA); 
	offset = 0;
	ID3D11DeviceContext*  deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexbuffer = m_vertexBuffer->buffer();
	deviceContext->IASetVertexBuffers(0, 1, &vertexbuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer->buffer(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	bool  result = effect->commit();

	deviceContext->DrawIndexed(m_indexCount, 0, 0);

	return true;
}