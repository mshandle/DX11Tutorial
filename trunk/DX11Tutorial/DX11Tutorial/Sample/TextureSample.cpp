#include "TextureSample.h"
#include "base/VertexFormat.h"
#include "base/EngineBase.h"
#include "framework/SystemClass.h"
#include "Camare/ClientCamera.h"

TextureSample::TextureSample(void):
				m_indexBuffer(NULL),
				m_vertexBuffer(NULL),
				m_ptexture(NULL),
				m_pshader(NULL)
{

}

TextureSample::~TextureSample(void)
{
}

bool TextureSample::init()
{
	XYZUV* vertices = NULL;
	unsigned long* indices = NULL;
	bool result = true;

	// Set the number of vertices in the vertex array.
	m_vertexCount = 4;

	// Set the number of indices in the index array.
	m_indexCount = 6;

	// Create the vertex array.
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

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	vertices[0].uv = D3DXVECTOR2(1.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);  // Top middle.
	vertices[1].uv = D3DXVECTOR2(0.0f, 0.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	vertices[2].uv = D3DXVECTOR2(1.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertices[3].uv = D3DXVECTOR2(0.0f, 1.0f);
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
		result =m_vertexBuffer->init(sizeof(XYZUV) * m_vertexCount, (void*)vertices, sizeof(XYZUV));
		SAFE_DELETE(vertices);
	}

	m_indexBuffer = new D3DIndexBuffer();
	if(m_indexBuffer)
	{
		result = m_indexBuffer->init(sizeof(unsigned long) * m_indexCount, (void*)indices);
		SAFE_DELETE(indices);
	}

	m_ptexture = new Texture();
	if(m_ptexture)
	{
		result = m_ptexture->initWithFile(L"../res/texture/db_doty_shatu003.dds");
	}
	m_pshader = new TextureShaderClass();
	if(m_pshader)
	{
		result = m_pshader->Initialize(SystemClass::Instance().renderModul()->GetDevice(), *SystemClass::Instance().HWnd());
	}
	
	ClientCamera::instance().SetPosition(0.0f, 0.0f, -10.0f);

	return result;
}

void TextureSample::fini()
{
	SAFE_DELETE(m_vertexBuffer);
	SAFE_DELETE(m_indexBuffer);
	//TODO:
}

void TextureSample::update( float det )
{
	//TODO:
}

bool TextureSample::render()
{
	unsigned int stride;
	unsigned int offset;
	// Set vertex buffer stride and offset.
	stride = sizeof(XYZUV); 
	offset = 0;
	ID3D11DeviceContext*  deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexbuffer = m_vertexBuffer->buffer();
	deviceContext->IASetVertexBuffers(0, 1, &vertexbuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer->buffer(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	m_pshader->Render(deviceContext,m_indexCount,world,IMath::MATRIX4X4TODX(ClientCamera::instance().GetViewMatrix()), IMath::MATRIX4X4TODX(SystemClass::Instance().renderModul()->GetProjectionMatrix()),m_ptexture->GetShaderResource() );

	return true;
}