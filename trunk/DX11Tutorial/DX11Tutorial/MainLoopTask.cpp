#include "MainLoopTask.h"


MainTaskManager::MainTaskManager()
{

}


MainTaskManager::~MainTaskManager()
{

}


MainTaskManager& MainTaskManager::Instance()
{
	static MainTaskManager instance;
	return instance;
}



void MainTaskManager::add( TASK_TAG tag, MainTask* app )
{
	task_map[tag] = app;
}

void MainTaskManager::del( TASK_TAG tag )
{
	TASK_MAP::iterator it = task_map.find(tag);
	if(it !=  task_map.end())
		task_map.erase(it);
}

int MainTaskManager::size()
{
	return task_map.size();
}


void MainTaskManager::sort()
{
	//TODO:
}

bool MainTaskManager::init()
{
	TASK_MAP::iterator it = task_map.begin();
	for(; it != task_map.end(); it++)
	{
		if(!it->second->init())
			return false;
	}	
	return true;
}

void MainTaskManager::fini()
{
	TASK_MAP::iterator it = task_map.begin();
	for(; it != task_map.end(); it++)
	{
		it->second->fini();
	}
}

void MainTaskManager::update( float deltime )
{
	TASK_MAP::iterator it = task_map.begin();
	for(; it != task_map.end(); it++)
	{
		it->second->update(deltime);
	}
}

bool MainTaskManager::render()
{
	TASK_MAP::iterator it = task_map.begin();
	for(; it != task_map.end(); it++)
	{
		if(!it->second->render())
			return false;
	}
	return true;
}