#include "Texture.h"
#include "SystemClass.h"
#include <iostream>

Texture::Texture(void):
				m_ptexture(NULL)
{

}

Texture::~Texture(void)
{
}

bool Texture::init( WCHAR* filename )
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(SystemClass::Instance().renderModul()->GetDevice(), filename,NULL, NULL, &m_ptexture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Load the texture in.
	return true;
}

void Texture::fini()
{
	SAFE_RELEASE(m_ptexture)
}

ID3D11ShaderResourceView* Texture::getTexture()
{
	return m_ptexture;
}