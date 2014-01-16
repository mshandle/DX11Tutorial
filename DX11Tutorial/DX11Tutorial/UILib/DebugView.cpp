#include "DebugView.h"
#include "TextureView.h"
#include "FrontLable.h"
#include "..\FrameWork\SystemClass.h"
#include "UISystem.h"
#include "..\Util\FpsClass.h"
#include "..\Util\CpuUseage.h"
BEGINUINAMESPACE


DebugView::DebugView()
{

}

DebugView::~DebugView()
{

}


void DebugView::init()
{
	FpsClass* fps =SystemClass::Instance().FPS();
	char fpsBuffer[256];
	sprintf(fpsBuffer,"FPS:%d",fps->getFps());
	m_FpsLable = new EVAUI::FrontLable(std::string(fpsBuffer), Vector2(EVAUI::UISystem::instance().TopRight().x - 100,EVAUI::UISystem::instance().TopRight().y-45));
	EVAUI::UISystem::instance().Root()->addchild(m_FpsLable);

	CpuUseage* cpu = SystemClass::Instance().CPU();
	sprintf(fpsBuffer,"CPU use: %d",cpu->GetCpuPercentage());

	m_CpuLable = new EVAUI::FrontLable(std::string(fpsBuffer), Vector2(EVAUI::UISystem::instance().TopRight().x - 100,EVAUI::UISystem::instance().TopRight().y-60));
	EVAUI::UISystem::instance().Root()->addchild(m_CpuLable);
}


void DebugView::update( float det )
{

	FpsClass* fps =SystemClass::Instance().FPS();
	CpuUseage* cpu = SystemClass::Instance().CPU();
	char fpsBuffer[256];
	sprintf(fpsBuffer,"FPS:%d",fps->getFps());
	m_FpsLable->setString(std::string(fpsBuffer));

	sprintf(fpsBuffer,"CPU use:%d",cpu->GetCpuPercentage());
	m_CpuLable->setString(std::string(fpsBuffer));
	//UIObject::update(det);
}

/*void DebugView::visit( Matrix4x4 world )
{

}

void DebugView::draw( Matrix4x4 world )
{

}*/
ENDUINAMESPACE