#include "Sample_Task.h"
#include "BufferAndShaderSample.h"
#include "EngineBase.h"
Sample_Task::Sample_Task(void):m_psample(NULL)
{
	MainTaskManager::Instance().add(TASK_SAMPLE, this);
}

Sample_Task::~Sample_Task(void)
{
	MainTaskManager::Instance().del(TASK_SAMPLE);
}

bool Sample_Task::init()
{
	m_psample = new BufferAndShaderSample();
	if(NULL != m_psample)
		return m_psample->init();
	return false;
}

void Sample_Task::fini()
{
	m_psample->fini();
	SAFE_RELEASE(m_psample);
}

void Sample_Task::update( float det )
{
	m_psample->update(det);
}

bool Sample_Task::render()
{
	m_psample->render();
	return true;
}