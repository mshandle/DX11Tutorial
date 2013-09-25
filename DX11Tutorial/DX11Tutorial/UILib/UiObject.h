/********************************************************************
	created:	2013/09/24
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\UILib\UiObject.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#ifndef UIOBJECT_H_
#define UIOBJECT_H_
#include <vector>
#include "UIdefind.h"
#include "math/IMath.h"
BEGINUINAMESPACE
class UIObject
{
public:

	UIObject(){m_bdirty = false;}
	typedef std::vector<UIObject*> VOBJECT;

	virtual void update(float det);

	virtual void visit(Matrix4x4 world);

	virtual void draw(Matrix4x4 world);

public:

	void	addchild(UIObject* pObject);

	void	remove(UIObject* pObject);

protected:

	VOBJECT m_Objects;

	UIObject* m_parent;

	bool m_bdirty;
};

ENDUINAMESPACE


#endif//UIOBJECT_H_