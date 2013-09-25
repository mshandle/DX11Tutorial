
/********************************************************************
	created:	2013/08/27
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\Sample\TextureUITest.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#include "SampleInterface.h"
#include "..\Render\Effect.h"
#include "..\Render\Texture.h"
#include "..\Render\D3DVertexBuffer.h"
#include "..\Render\D3DIndexBuffer.h"
class TextureUITest: public BaseSample
{
public:
	TextureUITest()
	{

	}

	~TextureUITest()
	{

	}


public:

	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();

private:

	Effect* m_pXYZUVEffect;

	unsigned int m_vertexCount;

	unsigned int m_indexCount;
	D3DVertexBuffer* m_vertexBuffer;
	D3DIndexBuffer*	m_indexBuffer;
	Texture*		m_ptexture;
};