#include "UISystem.h"
#include "Base/EngineBase.h"
#include "../FrameWork/SystemClass.h"
#include "DebugView.h"

BEGINUINAMESPACE


UISystem& UISystem::instance()
{
	static UISystem g_instance;
	return g_instance;
}

bool UISystem::init()
{
	bool result = true;

	m_pRoot = new UIObject();
	if(NULL != m_pRoot) result=  true;
	else result =  false;

	if(!result)return false;

	Effect* effect = new Effect();
	result = effect->load("../res/shader/uixyzuv.xml");
	m_Effects[UIET_XYZUV] = effect;

	
	m_pFont = new FontClass();

	result = m_pFont->Initialize("../res/font/fontdata.data",L"../res/font/font.dds");
	
	
	DebugView* pDebugView = new DebugView();
	pDebugView->init();
	m_pRoot->addchild(pDebugView);


	return result;
}

void UISystem::fini()
{
	SAFE_DELETE(m_pRoot);
}

UIObject* UISystem::Root()
{
	return m_pRoot;
}

Effect* UISystem::EffectType( UIEFFECTTYPE type_ )
{
	return m_Effects[type_];
}

Vector2 UISystem::TopLeft()
{
	return Vector2(- SystemClass::Instance().renderModul()->ViewWidth()/2.0f,SystemClass::Instance().renderModul()->ViewHeight()/2);
}

Vector2 UISystem::TopMid()
{
	return Vector2(0,SystemClass::Instance().renderModul()->ViewHeight()/2);
}

Vector2 UISystem::TopRight()
{
	return Vector2(SystemClass::Instance().renderModul()->ViewWidth()/2.0f,SystemClass::Instance().renderModul()->ViewHeight()/2);
}

FontClass* UISystem::FontEngine()
{
	return m_pFont;
}
ENDUINAMESPACE