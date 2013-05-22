#include "Camera_Task.h"
#include "ClientCamera.h"

Camera_Task::Camera_Task(void)
{
	MainTaskManager::Instance().add(TASK_CAMERA, this);
}

Camera_Task::~Camera_Task(void)
{
	MainTaskManager::Instance().del(TASK_CAMERA);
}

bool Camera_Task::init()
{
	return ClientCamera::instance().init();
}

void Camera_Task::fini()
{

}

void Camera_Task::update( float delTime )
{
	ClientCamera::instance().update(delTime);
}

bool Camera_Task::render()
{
	return true;
}