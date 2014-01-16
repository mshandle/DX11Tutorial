#pragma once

#pragma comment(lib, "pdh.lib")

#include <pdh.h>

class CpuUseage
{

public:

	CpuUseage();

	~CpuUseage();

public:

	bool init();

	void update(float det);

	void Shutdown();

	int	 GetCpuPercentage();

private:

	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;
};