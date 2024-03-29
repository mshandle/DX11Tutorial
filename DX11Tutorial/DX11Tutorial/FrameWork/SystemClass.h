
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "input/inputclass.h"
#include "render/d3dclass.h"

class FpsClass;
class CpuUseage;

class SystemClass:public InputHandler
{
private:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();
public:
	static SystemClass& Instance();
	bool				Initialize();

	void				Shutdown();

	void				Run();
	
	LRESULT CALLBACK	MessageHandler(HWND, UINT, WPARAM, LPARAM);
	
	D3DClass*			renderModul();
	
	HWND*				HWnd();

	void				WarningDialog(WCHAR* tile, WCHAR* Msg); 

					

	FpsClass*			FPS();

	CpuUseage*			CPU();
private:
	void calculateFrameTime();
	
	bool Frame();
	
	void InitializeWindows(int&, int&);
	
	void ShutdownWindows();
	 
	
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	D3DClass* m_D3D;
	float totalTime_;
	uint64 lastTime_;
	float dTime_;
	float fps_;

	FpsClass*	pFpsClass;

	CpuUseage*	pCpuClass;
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



#endif