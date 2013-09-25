
/********************************************************************
	created:	2013/09/23
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\Render\Terrain\TerrainBaseBlock.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#ifndef TERRAINBASEBLOCK_H_
#define TERRAINBASEBLOCK_H_
#include "../D3DIndexBuffer.h"
#include "../D3DVertexBuffer.h"
#include "Base/EngineBase.h"

class TerrainBaseBlock
{
public:
	TerrainBaseBlock():
	m_pIndexBuffer(NULL),
	m_pVertexBuffer(NULL)
	{}

	~TerrainBaseBlock()
	{
		SAFE_DELETE(m_pIndexBuffer);
		SAFE_DELETE(m_pVertexBuffer);
	}

public:

	bool	init(WCHAR* pFileName);

	void	update(float det);

	void	draw(const Matrix4x4& world_);

private:

	D3DIndexBuffer* m_pIndexBuffer;

	D3DVertexBuffer* m_pVertexBuffer;


};
#endif//TERRAINBASEBLOCK_H_