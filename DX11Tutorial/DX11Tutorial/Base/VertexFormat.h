#ifndef VERTEXFORMAT_H_
#define VERTEXFORMAT_H_
#include <d3d11.h>
#include <d3dx10math.h>

struct XYZRGBA
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct XYZN
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
};

struct XYZUV
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;
};

struct XYZNUV
{
	XYZNUV()
	{
		position = D3DXVECTOR3(0.0f,0.0f,0.0f);
		normal = D3DXVECTOR3(0.0f,0.0f,0.0f);
		uv = D3DXVECTOR2(0.0f,0.0f);
	}
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 uv;
};
#endif//VERTEXFORMAT_H_