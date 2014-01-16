/********************************************************************
	created:	2014/01/16
	filename: 	D:\evad11engine\DX11Tutorial\DX11Tutorial\Util\FpsClass.h
	file ext:	h
	author:		wubaoqing
	
	purpose:	
*********************************************************************/


#pragma  once

class FpsClass
{
public:

	FpsClass();

	~FpsClass();

public:
	
	bool Initialize();

	void update(float det);


	int	 getFps();

private:

	int m_fps, m_count;
	unsigned long m_startTime;
};