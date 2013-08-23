#ifndef _WORLD_TASK_H_
#define _WORLD_TASK_H_

#include "mainlooptask.h"

class World_Task :
	public MainTask
{
public:
	World_Task(void);
	~World_Task(void);

public:
	bool init();

	void fini();

	void update(float det);

	bool render();

private:
	static World_Task instance;
};
#endif//_WORLD_TASK_H_