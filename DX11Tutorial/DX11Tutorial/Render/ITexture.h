/********************************************************************
	created:	2013/09/27
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\Render\ITexture.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/


#ifndef ITEXTURE_H_
#define ITEXTURE_H_


class ITexture
{

public:
	virtual ID3D11ShaderResourceView* GetShaderResource()=0;
};

#endif//ITEXTURE_H_