
/********************************************************************
	created:	2014/01/09
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\UILib\DebugView.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#ifndef DEBUGVIEW_H_
#define DEBUGVIEW_H_
#include "UiObject.h"

BEGINUINAMESPACE

class TextureView;
class FrontLable;
class DebugView :public UIObject
{
public:
	DebugView();
	~DebugView();

public:

	virtual	void init();

	virtual void update(float det);

	/*virtual void visit(Matrix4x4 world);

	virtual void draw(Matrix4x4 world);*/

private:

	TextureView*	m_bg;

	FrontLable*		m_FpsLable;

	FrontLable*		m_CpuLable;

};
ENDUINAMESPACE
#endif DEBUGVIEW_H_