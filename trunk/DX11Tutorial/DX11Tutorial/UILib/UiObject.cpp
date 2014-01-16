#include "UiObject.h"

BEGINUINAMESPACE


UIObject::UIObject():m_bdirty(false),
					 m_nZoder(0)
{

}

UIObject::~UIObject()
{

}

void UIObject::update( float det )
{
	for(VOBJECT::iterator It = m_Objects.begin(); It != m_Objects.end(); It++)
	{
		(*It)->update(det);
	}
}

void UIObject::draw( Matrix4x4 world )
{
	//TODO:
}

void UIObject::addchild( UIObject* pObject ,int Zorder_)
{
	pObject->setZorder(Zorder_);
	pObject->m_parent = this;
	m_Objects.push_back(pObject);
}

void UIObject::remove( UIObject* pObject )
{
	for(VOBJECT::iterator It = m_Objects.begin(); It != m_Objects.end(); It++)
	{
		if((*It) == (pObject))
		{
			m_Objects.erase(It);
			return;
		}
	}
}

void UIObject::visit(Matrix4x4 world)
{
	//sort
	sortChilds();
	//draw self
	this->draw(world);
	//draw children
	for(VOBJECT::iterator It = m_Objects.begin(); It != m_Objects.end(); It++)
	{
		(*It)->visit(world);
	}


}

int UIObject::getZorder()
{
	return m_nZoder;
}

void UIObject::setZorder( int value_ )
{
	m_nZoder = value_;
}

void UIObject::sortChilds()
{
	//TODO:
}

void UIObject::removeAllChildren()
{
	for (VOBJECT::iterator It = m_Objects.begin(); It != m_Objects.end(); It++)
	{
		delete (*It);
	}
	m_Objects.clear();
}
ENDUINAMESPACE