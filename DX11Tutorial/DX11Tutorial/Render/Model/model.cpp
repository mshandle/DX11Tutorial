#include "model.h"

Model::Model( D3DVertexBuffer* pVertBuffer, D3DIndexBuffer* pIndexBuffer )
{
	m_pVertBuffer = pVertBuffer;

	m_pIndexBuffer = pIndexBuffer;
}

D3DIndexBuffer* Model::IndexBuffer()
{
	return m_pIndexBuffer;
}

D3DVertexBuffer* Model::VertBuffer()
{
	return m_pVertBuffer;
}