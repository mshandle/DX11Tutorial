
#pragma once
#include <string>

class Effect
{
public:
	Effect(void);
	~Effect(void);

public:
	bool load(const char* filename);
	
	bool commit();
private:
	
};
