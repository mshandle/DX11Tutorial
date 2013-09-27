#pragma once
#include "sampleinterface.h"
#include "render/D3DVertexBuffer.h"
#include "render/D3DIndexBuffer.h"
#include "../Render/Effect.h"
#include "../Render/Texture.h"
#include "../Render/Model/model.h"
#include "../UILib/TextureView.h"

class ModleLoaderSample :
	public BaseSample
{
public:
	ModleLoaderSample(void);
	~ModleLoaderSample(void);
public:
	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();

private:
	
	Model* m_pModel;

	Effect* m_peffect;

	Texture* m_pTexturel;

	EVAUI::TextureView* pTextureView;
};
