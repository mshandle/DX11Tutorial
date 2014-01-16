#include "FpsClass.h"
#include <windows.h>
#include <mmsystem.h>
FpsClass::FpsClass()
{

}

FpsClass::~FpsClass()
{

}

bool FpsClass::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	return true;
}

void FpsClass::update( float det )
{
	m_count++;

	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;

		m_startTime = timeGetTime();
	}
}

int FpsClass::getFps()
{
	return m_fps;
}