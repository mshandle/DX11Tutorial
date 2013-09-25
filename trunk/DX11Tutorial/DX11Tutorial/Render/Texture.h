#pragma once

#include <d3d11.h>
#include <d3dx11tex.h>

class Texture
{
public:
	Texture(void);
	~Texture(void);
public:
	bool init(WCHAR* filename);

	void fini();

	ID3D11ShaderResourceView* getTexture();


private:

	float m_nHeight;

	float m_nWidht;
	ID3D11ShaderResourceView* m_ptexture;
};
