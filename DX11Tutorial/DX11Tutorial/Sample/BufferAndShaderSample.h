#pragma once


#include <d3d11.h>
#include <d3dx10math.h>

#include "sampleinterface.h"
#include "render/ColorShaderClass.h"
#include "render/D3DVertexBuffer.h"
#include "render/D3DIndexBuffer.h"


class BufferAndShaderSample :
	public BaseSample
{
public:
	BufferAndShaderSample(void);
	~BufferAndShaderSample(void);
public:
	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();
private:

	D3DVertexBuffer* m_vertexBuffer;
	D3DIndexBuffer* m_indexBuffer;
	int m_vertexCount, m_indexCount;

	ColorShaderClass* m_pshader;
};
