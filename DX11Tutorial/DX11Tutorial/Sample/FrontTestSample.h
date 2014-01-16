
/********************************************************************
	created:	2013/09/27
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\FrontTestSample.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/

#ifndef FRONTTESTSAMPLE_H_
#define FRONTTESTSAMPLE_H_

#include "Sample/SampleInterface.h"
#include "../UILib/FrontLable.h"

class FrontTestSample: public BaseSample
{
public:
	FrontTestSample()
	{

	}

	~FrontTestSample()
	{

	}


public:

	virtual bool init();

	virtual void fini();

	virtual void update(float det);

	virtual bool render();

private:

	EVAUI::FrontLable* pLable;
};

#endif//FRONTTESTSAMPLE_H_