#pragma once
#include "sampleinterface.h"
#include "D3DVertexBuffer.h"
#include "D3DIndexBuffer.h"

class ModleLoaderSample :
	public BaseSample
{
public:
	ModleLoaderSample(void);
	~ModleLoaderSample(void);
public:
	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();
private:
private:
	D3DVertexBuffer* m_vertexBuffer;
	D3DIndexBuffer* m_indexBuffer;
};
