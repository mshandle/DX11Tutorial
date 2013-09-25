#include "UiObject.h"

BEGINUINAMESPACE


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

void UIObject::addchild( UIObject* pObject )
{
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
	this->draw(world);

	for(VOBJECT::iterator It = m_Objects.begin(); It != m_Objects.end(); It++)
	{
		(*It)->visit(world);
	}


}
ENDUINAMESPACE