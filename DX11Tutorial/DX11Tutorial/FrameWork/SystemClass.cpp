
#include "systemclass.h"
#include <mmsystem.h>

#include "World_Task.h"
#include "Camera_Task.h"
#include "Input_Task.h"
#include "Sample_Task.h"
#include "GUI_Task.h"
#include "UILib/UISystem.h"
#include "Util/FpsClass.h"
#include "Util/CpuUseage.h"

#pragma comment( lib,"winmm.lib" )

World_Task World_Task::instance;
Camera_Task Camera_Task::instance;
Input_Task Input_Task::instance;
Sample_Task Sample_Task::instance;
GUI_Task	GUI_Task::instance;

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

SystemClass::SystemClass():
							dTime_(0.f), 
							totalTime_(0.f),
							fps_(0),
							pFpsClass(NULL),
							pCpuClass(NULL)
{
	m_D3D = NULL;
	lastTime_ =  timeGetTime();
}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	screenWidth = 0;
	screenHeight = 0;

	InitializeWindows(screenWidth, screenHeight);

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	/*m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	*/
	m_D3D = new D3DClass();
	if(!m_D3D)return false;

	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, m_hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
	
	pFpsClass = new FpsClass();
	pFpsClass->Initialize();

	pCpuClass = new CpuUseage();
	pCpuClass->init();

	EVAUI::UISystem::instance().init();
	MainTaskManager::Instance().init();

	
	return true;
}


void SystemClass::Shutdown()
{
	// Release the graphics object.

	SAFE_DELETE(pFpsClass);
	pCpuClass->Shutdown();


	SAFE_DELETE(m_D3D);

	MainTaskManager::Instance().fini();
	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}

	}

	return;
}


bool SystemClass::Frame()
{
	bool result;


	// Check if the user pressed escape and wants to exit the application.
	if(InputDevice::Instance()->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	calculateFrameTime();

	MainTaskManager::Instance().update(dTime_);
	// Do the frame processing for the graphics object.
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 0.0f);

	result =  MainTaskManager::Instance().render();
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	if(!result)
	{
		return false;
	}

	return true;
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
		case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			InputDevice::Instance()->KeyDown((unsigned int)wparam);
			return 0;
		}

		// Check if a key has been released on the keyboard.
		case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			InputDevice::Instance()->KeyUp((unsigned int)wparam);
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
		default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;



	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	//screenWidth = 1024;
	//screenHeight = 768;
	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = 1024;
		screenHeight = 768;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}
	UINT style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP|WS_CAPTION|WS_SYSMENU;
	RECT     windowRect;
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = screenWidth;
	windowRect.bottom = screenHeight;
	AdjustWindowRect(&windowRect, style, false);

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP|WS_CAPTION|WS_SYSMENU,
							posX,
							posY,
							windowRect.right - windowRect.left,
							windowRect.bottom - windowRect.top, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(true);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	return;
}

SystemClass& SystemClass::Instance()
{
	static SystemClass instance;
	return instance;
}

void SystemClass::calculateFrameTime()
{

	 uint64 thisTime = timeGetTime();

	dTime_ = float( ((double)(uint64)(thisTime - lastTime_)) /
		1000.f );

	totalTime_ += dTime_;
	lastTime_ = thisTime;
	fps_ = 1.0f/ dTime_;

	pFpsClass->update(dTime_);
	pCpuClass->update(dTime_);
}

D3DClass* SystemClass::renderModul()
{
	return m_D3D;
}

HWND* SystemClass::HWnd()
{
	return &m_hwnd;
}

void SystemClass::WarningDialog( WCHAR* tile, WCHAR* Msg )
{
	MessageBox(m_hwnd, tile, Msg, MB_OK);
}

FpsClass* SystemClass::FPS()
{
	return pFpsClass;
}

CpuUseage* SystemClass::CPU()
{
	return pCpuClass;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return SystemClass::Instance().MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}