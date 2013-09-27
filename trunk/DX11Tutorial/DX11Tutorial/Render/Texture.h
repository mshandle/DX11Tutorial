#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>
#include "ITexture.h"
class Texture : public ITexture
{
public:
	Texture(void);
	~Texture(void);
public:
	bool initWithFile(WCHAR* filename);

	void fini();

	ID3D11ShaderResourceView* GetShaderResource();


private:

	float m_nHeight;

	float m_nWidht;
	ID3D11ShaderResourceView* m_ptexture;
};
