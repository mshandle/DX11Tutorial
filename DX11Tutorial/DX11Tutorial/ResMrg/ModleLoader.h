#pragma once
#include "render/D3DVertexBuffer.h"
#include "render/D3DIndexBuffer.h"
#include "Render/Model/model.h"
class ModleLoader
{
private:
	ModleLoader(void);
	~ModleLoader(void);
public:
	struct FaceType
	{
		FaceType()
		{
			vIndex1= vIndex2=  vIndex3 = -1;

			tIndex1 = tIndex2= tIndex3 = -1;

			nIndex1  = nIndex2 = nIndex3 = -1;
		}

		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	};

public:
	static ModleLoader& Instance();

	Model* loaderModel(WCHAR* _modlefile, D3DVertexBuffer** vbuffer, D3DIndexBuffer** ibuffer);
};
