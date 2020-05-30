#pragma once
#include <Windows.h>
#ifndef __WINDOW_H__
#define __WINDOW_H__



typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;
class CRenderer;
class CMesh;
class CWindow {
public:

    bool WinInitilize(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

    void SetClientSize(HWND _hwnd, int width, int height);


    void DispUpdate();
    //void ObjectDisp(float add);
    //GLint CreateVAO(GLuint verticesCount, const GLfloat* position , GLint program);
private:


    WNDCLASS m_wc;
    HWND m_hwnd;
    HDC m_hdc;
    HGLRC m_glrc;

    CRenderer* m_prenderer;


    CMesh* testMesh;
    CMesh* testMesh2;
    //GLuint vboID = -1;
    //GLuint vaoID = -1;
    GLuint m_programID = -1;

    GLuint uniform_color = -1;
    GLuint uniform_modelMat = -1;
};




#endif // !__WINDOW_H__
