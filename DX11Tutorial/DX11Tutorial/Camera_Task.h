#pragma once
#include "mainlooptask.h"

class Camera_Task :
	public MainTask
{
public:
	Camera_Task(void);
	~Camera_Task(void);

public:
	bool init();

	void fini();

	void update(float delTime);

	bool render();
private:
	static Camera_Task instance;
};
