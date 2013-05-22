#include "D3DIndexBuffer.h"
#include "SystemClass.h"

D3DIndexBuffer::D3DIndexBuffer(void):
					m_indexbuffer(NULL),
					m_mensize(0)
{
}

D3DIndexBuffer::~D3DIndexBuffer(void)
{
	fini();
}

bool D3DIndexBuffer::init( unsigned int size, void* memory )
{
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;


	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = size;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = memory;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = SystemClass::Instance().renderModul()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexbuffer);
	if(FAILED(result))
	{
		return false;
	}
	return true;
}

ID3D11Buffer* D3DIndexBuffer::buffer()
{
	return m_indexbuffer;
}

void D3DIndexBuffer::fini()
{
	if(NULL != m_indexbuffer)
	{
		m_indexbuffer->Release();
		m_indexbuffer = NULL;
	}
}