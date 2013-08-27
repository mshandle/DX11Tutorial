/********************************************************************
	created:	2013/08/26
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\Render\Model\model.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/


#ifndef MODLE_H_
#define MODLE_H_

#include "../D3DIndexBuffer.h"
#include "../D3DVertexBuffer.h"
class Model
{

public:
	
	Model() {};
	
	Model(D3DVertexBuffer* pVertBuffer, D3DIndexBuffer* pIndexBuffer, int ntris);

	virtual ~Model(){};

public:

	D3DIndexBuffer*		IndexBuffer();

	D3DVertexBuffer*	VertBuffer();

	unsigned int		TrisNum();
public:

	D3DVertexBuffer*	m_pVertBuffer;

	D3DIndexBuffer*		m_pIndexBuffer;

	unsigned int		m_untris;
};

#endif//MODLE_H_