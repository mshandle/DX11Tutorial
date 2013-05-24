#pragma once
#include "sampleinterface.h"
#include "D3DVertexBuffer.h"
#include "D3DIndexBuffer.h"
#include "Texture.h"
#include "TextureShaderClass.h"
class TextureSample :
	public BaseSample
{
public:
	TextureSample(void);
	~TextureSample(void);
public:
	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();
private:

	D3DVertexBuffer* m_vertexBuffer;
	D3DIndexBuffer* m_indexBuffer;

	Texture* m_ptexture;
	int m_vertexCount, m_indexCount;
	TextureShaderClass* m_pshader;
};
