#pragma once
#ifndef __OPENGL_DEVICE_H__
#define __OPENGL_DEVICE_H__

#include <Windows.h>

class COpenglDevice {
public:
	bool Initilize(HWND _hwnd);
	void SwapBuffer();
	void Finalize();
private:
	HWND m_hwnd = HWND();
	HDC m_hdc = HDC();
	HGLRC m_glrc = HGLRC();
};

#endif // !__OPENGL_DEVICE_H__
