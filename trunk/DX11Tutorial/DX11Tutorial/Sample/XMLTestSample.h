#pragma once
#include "SampleInterface.h"
#include "render/Effect.h"
#include "render/D3DVertexBuffer.h"
#include "render/D3DIndexBuffer.h"
#include "render/Texture.h"
class XMLTestSample:public BaseSample
{
public:
	XMLTestSample(void);
	~XMLTestSample(void);
public:
	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();
private:
	D3DVertexBuffer* m_vertexBuffer;
	D3DIndexBuffer* m_indexBuffer;
	int m_vertexCount, m_indexCount;

	Texture* m_ptexture;
	Effect* effect;
};
