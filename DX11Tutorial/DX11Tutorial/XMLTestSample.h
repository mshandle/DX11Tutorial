#pragma once
#include "SampleInterface.h"
class XMLTestSample:public BaseSample
{
public:
	XMLTestSample(void);
	~XMLTestSample(void);
public:
	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();
};
