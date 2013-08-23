#include "World_Task.h"


World_Task::World_Task(void)
{
	MainTaskManager::Instance().add(TASK_WORLD, this);
}

World_Task::~World_Task(void)
{
	MainTaskManager::Instance().del(TASK_WORLD);
}

bool World_Task::init()
{
	return true;
}

void World_Task::fini()
{

}

void World_Task::update( float det )
{

}

bool World_Task::render()
{
	return true;
}