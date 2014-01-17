
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
#include "../Effect.h"

class TerrainBaseBlock
{
public:

	struct HeightMapType 
	{ 
		float x, y, z;
		float nx, ny, nz;
	};

public:
	TerrainBaseBlock():
	m_vertexBuffer(NULL),
	m_indexBuffer(NULL)
	{}

	~TerrainBaseBlock()
	{
		SAFE_DELETE(m_vertexBuffer);
		SAFE_DELETE(m_indexBuffer);
	}

public:

	bool	init(char* pFileName);

	bool	initWith();

	void	update(float det);

	void	draw(const Matrix4x4& world_);

	bool	loadHeight(char* filename);

	bool	CalculateNormals();

private:

	int m_terrainWidth, m_terrainHeight;
	int m_vertexCount, m_indexCount;
	D3DVertexBuffer *m_vertexBuffer;
	D3DIndexBuffer	*m_indexBuffer;

	Effect*			peffect;

	HeightMapType*		m_heightMap;


};
#endif//TERRAINBASEBLOCK_H_