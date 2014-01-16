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

	UIObject();

	~UIObject();

	typedef std::vector<UIObject*> VOBJECT;

public:

	virtual void update(float det);

	virtual void visit(Matrix4x4 world);

	virtual void draw(Matrix4x4 world);

public:

	void	addchild(UIObject* pObject,int zOder = 0);

	void	remove(UIObject* pObject);

	void	removeAllChildren();

	virtual int getZorder();


	virtual void setZorder(int value_);

private:

	virtual void sortChilds();

protected:

	VOBJECT		m_Objects;

	UIObject*	m_parent;

	bool		m_bdirty;

	int			m_nZoder;
};

ENDUINAMESPACE


#endif//UIOBJECT_H_