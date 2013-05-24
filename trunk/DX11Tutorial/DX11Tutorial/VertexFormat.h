#ifndef VERTEXFORMAT_H_
#define VERTEXFORMAT_H_
#include <d3d11.h>
#include <d3dx10math.h>

struct XYZRGBA
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct XYZUV
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;
};

#endif//VERTEXFORMAT_H_