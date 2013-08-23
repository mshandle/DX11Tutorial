////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"

InputDevice* InputDevice::g_device = NULL;
InputDevice::InputDevice()
{
}


InputDevice::InputDevice(const InputDevice& other)
{
}


InputDevice::~InputDevice()
{
}


void InputDevice::Initialize()
{
	int i;
	

	// Initialize all the keys to being released and not pressed.
	for(i=0; i<256; i++)
	{
		m_keys[i] = false;
	}

	return;
}


void InputDevice::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}


void InputDevice::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}


bool InputDevice::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}

InputDevice* InputDevice::Instance()
{
	if(NULL == g_device)
		g_device = new InputDevice();

	return g_device;
}

void InputDevice::fini()
{
	if(NULL != g_device)
	{
		delete g_device;
		g_device = NULL;
	}
}