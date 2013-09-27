#include "TextureView.h"
#include "Base/VertexFormat.h"
#include "FrameWork/SystemClass.h"
#include "Render/Effect.h"
#include "UISystem.h"
BEGINUINAMESPACE


TextureView::TextureView():
			m_pIndexBuffer(NULL),
			m_pVertexBuffer(NULL),
			m_pTexture(NULL)
{

}

TextureView::~TextureView()
{

}

Vector2 TextureView::Size()
{
	return m_positon;
}

void TextureView::Size( Vector2 size_ )
{
	if(m_vSize != size_)
	{
		m_vSize = size_;
		m_bdirty = true;
	}
}

Vector2 TextureView::position()
{
	return m_positon;
}

void TextureView::position( Vector2 position_ )
{
	if(m_positon != position_)
	{
		m_positon = position_;
		m_bdirty = true;
	}
	
}

void TextureView::draw( Matrix4x4 world )
{
	//return true;
	unsigned int offset;
	// Set vertex buffer stride and offset.
	offset = 0;
	ID3D11DeviceContext*  deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexbuffer = m_pVertexBuffer->buffer();
	unsigned int stride_ = m_pVertexBuffer->stride();
	deviceContext->IASetVertexBuffers(0, 1, &vertexbuffer, &stride_, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_pIndexBuffer->buffer(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Effect* pXYZUV = UISystem::instance().EffectType(UIET_XYZUV);

	if(NULL == m_pTexture) return;
	pXYZUV->setTexture("diffuse", m_pTexture->GetShaderResource());
	
	bool  result = pXYZUV->commit();

	deviceContext->DrawIndexed(6, 0, 0);

}

bool TextureView::initTextureFile( WCHAR* filename, int widht, int height )
{
	Texture*pTexture = new Texture();

	if(!pTexture->initWithFile(filename))
		return false;
	m_pTexture = pTexture;
	return initWithOutTexture(widht, height);

}

void TextureView::update( float det )
{
	if(!m_bdirty)
	{
		UIObject::update(det);
		return;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	
	XYZUV* vertices = NULL;
	XYZUV* verticesPtr = NULL;

	vertices = new XYZUV[4];
	// Create the index array.
	


	vertices[0].position = D3DXVECTOR3(m_positon.x, m_positon.y -m_vSize.y , 0.0f);  // Bottom left.
	vertices[0].uv = D3DXVECTOR2(0.0f,1.0);

	vertices[1].position = D3DXVECTOR3(m_positon.x, m_positon.y, 0.0f);  // Top left.
	vertices[1].uv = D3DXVECTOR2(0.0f,0.0);

	vertices[2].position = D3DXVECTOR3(m_positon.x +m_vSize.x ,  m_positon.y -m_vSize.y, 0.0f);  // Bottom right.
	vertices[2].uv = D3DXVECTOR2(1.0f,1.0);

	vertices[3].position = D3DXVECTOR3(m_positon.x +m_vSize.x, m_positon.y, 0.0f);//top right
	vertices[3].uv = D3DXVECTOR2(1.0f,0.0);


	ID3D11DeviceContext* deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();

	deviceContext->Map(m_pVertexBuffer->buffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	verticesPtr = (XYZUV*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(XYZUV) * 4));

	// Unlock the vertex buffer.
	deviceContext->Unmap(m_pVertexBuffer->buffer(), 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	UIObject::update(det);
}

bool TextureView::initWithOutTexture( int widht, int height )
{
	m_vSize.x = (float)widht;
	m_vSize.y = (float)height;

	// index buffer and vertex buffer

	bool result = true;
	XYZUV* vertices = NULL;
	unsigned long* indices = NULL;

	vertices = new XYZUV[4];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[6];
	if(!indices)
	{
		return false;
	}

	vertices[0].position = D3DXVECTOR3(m_positon.x, m_positon.y -m_vSize.y , 0.0f);  // Bottom left.
	vertices[0].uv = D3DXVECTOR2(0.0f,1.0);

	vertices[1].position = D3DXVECTOR3(m_positon.x, m_positon.y, 0.0f);  // Top left.
	vertices[1].uv = D3DXVECTOR2(0.0f,0.0);

	vertices[2].position = D3DXVECTOR3(m_positon.x +m_vSize.x ,  m_positon.y -m_vSize.y, 0.0f);  // Bottom right.
	vertices[2].uv = D3DXVECTOR2(1.0f,1.0);

	vertices[3].position = D3DXVECTOR3(m_positon.x +m_vSize.x, m_positon.y, 0.0f);//top right
	vertices[3].uv = D3DXVECTOR2(1.0f,0.0);
	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right
	indices[3] = 1;
	indices[4] = 3;
	indices[5] = 2;


	m_pVertexBuffer = new D3DVertexBuffer();
	if(m_pVertexBuffer)
	{
		result =m_pVertexBuffer->init(sizeof(XYZUV) * 4, (void*)vertices, sizeof(XYZUV),D3D11_USAGE_DYNAMIC);
		SAFE_DELETE(vertices);
	}

	m_pIndexBuffer = new D3DIndexBuffer();
	if(m_pIndexBuffer)
	{
		result = m_pIndexBuffer->init(sizeof(unsigned long) * 6, (void*)indices);
		SAFE_DELETE(indices);
	}

	return true;
}

void TextureView::setTexture( ITexture* pTexture )
{
	m_pTexture = pTexture;
}
ENDUINAMESPACE