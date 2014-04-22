#include "model.h"
#include "FrameWork/SystemClass.h"

Model::Model( D3DVertexBuffer* pVertBuffer, D3DIndexBuffer* pIndexBuffer, int ntris )
{
	m_pVertBuffer = pVertBuffer;

	m_pIndexBuffer = pIndexBuffer;

	m_untris = ntris;
}

D3DIndexBuffer* Model::IndexBuffer()
{
	return m_pIndexBuffer;
}

D3DVertexBuffer* Model::VertBuffer()
{
	return m_pVertBuffer;
}

unsigned int Model::TrisNum()
{
	return m_untris;
}

void Model::draw( Matrix4x4 world )
{
	unsigned int offset;
	// Set vertex buffer stride and offset.
	offset = 0;
	ID3D11DeviceContext*  deviceContext = SystemClass::Instance().renderModul()->GetDeviceContext();
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	ID3D11Buffer* vertexbuffer = m_pVertBuffer->buffer();
	unsigned int stride_ = m_pVertBuffer->stride();
	deviceContext->IASetVertexBuffers(0, 1, &vertexbuffer, &stride_, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_pIndexBuffer->buffer(), DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	unsigned int nIndexCount = TrisNum() * 3;

	deviceContext->DrawIndexed(nIndexCount, 0, 0);
}