#pragma  once
#include "SampleInterface.h"
#include "..\Render\D3DVertexBuffer.h"
#include "..\Render\D3DIndexBuffer.h"
#include "..\Render\Effect.h"
#include "..\Render\Terrain\TerrainBaseBlock.h"


class TerrainSample:public BaseSample
{
public:
	TerrainSample();

	~TerrainSample();

public:
	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();
private:


	D3DVertexBuffer* m_vertexBuffer;
	D3DIndexBuffer* m_indexBuffer;

	Effect*				peffect;

	TerrainBaseBlock*	pBlock;
	int m_vertexCount, m_indexCount;
};