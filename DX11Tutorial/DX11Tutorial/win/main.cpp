////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "framework/systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{

	bool result;
	
	// Initialize and run the system object.
	result = SystemClass::Instance().Initialize();
	if(result)
	{
		SystemClass::Instance().Run();
	}

	// Shutdown and release the system object.
	SystemClass::Instance().Shutdown();
	
	return 0;
}