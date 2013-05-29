#pragma once
#include "SampleInterface.h"
#include "Effect.h"
#include "D3DVertexBuffer.h"
#include "D3DIndexBuffer.h"
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
	Effect* effect;
};
