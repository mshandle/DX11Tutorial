#include "GUI_Task.h"
#include "UILib/UISystem.h"
#include "SystemClass.h"

GUI_Task::GUI_Task()
{
	MainTaskManager::Instance().add(TASK_GUI, this);
}

GUI_Task::~GUI_Task()
{
	MainTaskManager::Instance().del(TASK_GUI);
}

bool GUI_Task::init()
{	
	//return EVAUI::UISystem::instance().init();
	return true;
}

void GUI_Task::fini()
{
	EVAUI::UISystem::instance().fini();
}

void GUI_Task::update( float delTime )
{
	EVAUI::UISystem::instance().Root()->update(delTime);
}

bool GUI_Task::render()
{
	SystemClass::Instance().renderModul()->TurnOffDepth();
	EVAUI::UISystem::instance().Root()->visit(IMath::MAT4X4_IDENTITY);
	SystemClass::Instance().renderModul()->TurnOnDepth();
	return true;
}