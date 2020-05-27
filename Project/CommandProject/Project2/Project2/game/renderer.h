#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__
#include <Windows.h>

typedef unsigned int GLuint;
class CMesh;
class CRenderer {
public:
	bool Initialize(HWND _hwnd);
	void StartDisplay();
	void MeshDraw(const CMesh* _mesh);
	void EndDisplay();
	
private:
	bool GLSetUp(HWND _hwnd);
	void GLRelease();

	HWND m_hwnd;
	HDC m_hdc;
	HGLRC m_glrc;
};


#endif // !__RENDERER_H__