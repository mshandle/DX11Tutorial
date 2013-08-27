#include "model.h"

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