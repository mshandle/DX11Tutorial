#include "Input_Task.h"
#include "input/InputClass.h"

Input_Task::Input_Task(void)
{
	MainTaskManager::Instance().add(TASK_INPUT, this);
}

Input_Task::~Input_Task(void)
{
	MainTaskManager::Instance().del(TASK_INPUT);
}

bool Input_Task::init()
{
	InputDevice::Instance()->Initialize();
	return true;
}

void Input_Task::fini()
{
	InputDevice::fini();
}

void Input_Task::update( float det )
{
	//TODO:
}

bool Input_Task::render()
{
	//TODO:
	return true;
}