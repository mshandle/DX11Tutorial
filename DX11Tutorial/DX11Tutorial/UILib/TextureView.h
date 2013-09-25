/********************************************************************
	created:	2013/09/24
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\UILib\TextureView.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/




#ifndef TEXTUREVIEW_H_ 
#define TEXTUREVIEW_H_

#include "Base/EngineBase.h"
#include "UiObject.h"

#include "Render/D3DVertexBuffer.h"
#include "Render/D3DIndexBuffer.h"
#include "Render/Texture.h"

BEGINUINAMESPACE

class TextureView : public UIObject
{

public:

	TextureView();

	~TextureView();

public:


	Vector2 Size();

	void	Size(Vector2 size_);
	
	Vector2 position();

	void	position(Vector2 position_);

public:

	bool	init(WCHAR* filename, int widht, int height);

	void	draw(Matrix4x4 world);

	void	update(float det);

private:

	Vector2 m_vSize;

	Vector2 m_positon;

	D3DIndexBuffer* m_pIndexBuffer;

	D3DVertexBuffer* m_pVertexBuffer;

	Texture*		m_pTexture;


};

ENDUINAMESPACE
#endif//TEXTUREVIEW_H_