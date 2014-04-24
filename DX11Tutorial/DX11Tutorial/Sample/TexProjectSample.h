
/********************************************************************
	created:	2013/09/27
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\Sample\RTTSample.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/


#ifndef SHADOWMAPSAMPLE_H_
#define SHADOWMAPSAMPLE_H_

#include "SampleInterface.h"
#include "Render/Model/model.h"
#include "Render/Effect.h"
#include "Render/Texture.h"
#include "../UILib/TextureView.h"
#include "../Render/Texture2D.h"
class TexProjectSample: public BaseSample
{
public:
	TexProjectSample()
	{

	}

	~TexProjectSample()
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

	Texture* m_pTexturel;

	Texture2D* m_pRenderTarget;
	EVAUI::TextureView* DedugWindow;
};

#endif//SHADOWMAPSAMPLE_H_