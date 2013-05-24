#pragma once
#include "D3DVertexBuffer.h"
#include "D3DIndexBuffer.h"

class ModleLoader
{
private:
	ModleLoader(void);
	~ModleLoader(void);
	
	struct QuatFace
	{
		int face1;
		int face2;
		int face3;
		int face4;
	};

public:
	static ModleLoader& Instance();

	bool loaderModel(WCHAR* _modlefile, D3DVertexBuffer** vbuffer, D3DIndexBuffer** ibuffer);
};
