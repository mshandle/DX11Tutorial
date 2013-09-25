/********************************************************************
	created:	2013/09/24
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\FrameWork\GUI_Task.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#ifndef GUI_TASK_H_
#define GUI_TASK_H_

#include "MainLoopTask.h"


class GUI_Task : public MainTask
{
public:
	GUI_Task();

	~GUI_Task();

public:

	virtual bool init();

	virtual void fini();

	virtual void update(float delTime);

	virtual bool render();

private:

	static GUI_Task instance;
};

#endif//GUI_TASK_H_