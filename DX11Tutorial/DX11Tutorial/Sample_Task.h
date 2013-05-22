#pragma once
#include "mainlooptask.h"
#include "SampleInterface.h"
class Sample_Task :
	public MainTask
{
public:
	Sample_Task(void);
	~Sample_Task(void);
public:
	bool init();

	void fini();

	void update(float det);

	bool render();
private:
	static Sample_Task instance;

	BaseSample* m_psample;
};
