/********************************************************************
	created:	2013/09/24
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\UILib\UISystem.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#ifndef UISYSTEM_H_
#define UISYSTEM_H_

#include <map>
#include "UIdefind.h"
#include "UiObject.h"
#include "Render/Effect.h"
#include "fontclass.h"
BEGINUINAMESPACE

class UISystem
{
public:
	
	typedef std::map<UIEFFECTTYPE, Effect*> EffectMap;
public:

	static UISystem& instance();

public:

	bool init();

	void fini();

	UIObject* Root();

	Effect*	  EffectType(UIEFFECTTYPE type_);

	Vector2		TopLeft();

	Vector2		TopMid();

	Vector2		TopRight();

	FontClass*	FontEngine();

private:

	UISystem():m_pRoot(NULL){}

	~UISystem(){}

private:

	UIObject* m_pRoot;

	FontClass*	m_pFont;

	EffectMap m_Effects;
};

ENDUINAMESPACE


#endif//UISYSTEM_H_