#ifndef _MAINLOOPTASK_H_
#define _MAINLOOPTASK_H_

#include <map>

enum TASK_TAG
{
	TASK_APP,
	TASK_INPUT,
	TASK_CAMERA,
	TASK_WORLD,
	TASK_SAMPLE,
	TASK_GUI
};

class MainTask
{
public:
	virtual bool init()=0;

	virtual void fini()=0;

	virtual void update(float delTime)=0;

	virtual bool render()=0;
};

class MainTaskManager
{
public:
	typedef std::map<int, MainTask*> TASK_MAP;
public:
	static MainTaskManager& Instance();
public:
	void add(TASK_TAG tag, MainTask* app);

	void del(TASK_TAG tag);

	int  size();

	void sort();

	bool init();
	
	void fini();

	void update(float deltime);

	bool render();


private:
	MainTaskManager();
	~MainTaskManager();

private:
	TASK_MAP task_map;
};

#endif//_MAINLOOPTASK_H_