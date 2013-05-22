#pragma once
#include "mainlooptask.h"

class Input_Task :
	public MainTask
{
public:
	Input_Task(void);
	~Input_Task(void);
public:
	bool init();

	void fini();

	void update(float det);

	bool render();
private:
	static Input_Task instance;
};
