#ifndef SHADWOMAPSAMPLE_H_
#define SHADWOMAPSAMPLE_H_

#include "SampleInterface.h"
#include "Render/Model/model.h"
#include "Render/Effect.h"
#include "Render/Texture.h"
#include "../UILib/TextureView.h"
#include "../Render/Texture2D.h"
class ShadowMapSample: public BaseSample
{
public:
	ShadowMapSample()
	{

	}

	~ShadowMapSample()
	{

	}


public:

	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();

private:

	std::vector<Model*> m_pModel;

	Effect* m_peffect;

	Effect* m_pDepthMapEffect;

	Texture* m_pTexturel;
	Texture* diffuse;
	Texture2D* m_pRenderTarget;
	EVAUI::TextureView* DedugWindow;
};


#endif//SHADWOMAPSAMPLE_H_