#include "window.h"
#include <iostream>
#include "renderer.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include "input.h"


//test
#include "Mesh.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


float angle = 0;

bool CWindow::WinInitilize(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {



    m_wc.style = CS_HREDRAW | CS_VREDRAW;
    m_wc.lpfnWndProc = StaticWndProc;
    m_wc.cbClsExtra = 0;
    m_wc.cbWndExtra = 0;
    m_wc.hInstance = hInstance;
    m_wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    m_wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    m_wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
    m_wc.lpszMenuName = NULL;
    m_wc.lpszClassName = TEXT("MainWindow");

    RegisterClass(&m_wc);

    m_hwnd = CreateWindow(TEXT("MainWindow"),
        TEXT("ウィンドウ"),
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME,
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL);

    SetClientSize(m_hwnd, WINDOW_WIDTH, WINDOW_HEIGHT);

    AllocConsole();
    FILE* fp = NULL;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);




    ShowWindow(m_hwnd, nCmdShow);

    UpdateWindow(m_hwnd);

    Input::CreateInstance();
    Input::SetWnd(m_hwnd);
    //CreateMesh();
    //m_programID = CreateShader();
    return true;
}




void CWindow::DispUpdate() {

}

void CWindow::Finalize()
{
    FreeConsole();
}



LRESULT CALLBACK CWindow::StaticWndProc(HWND hWnd,
    UINT msg,
    WPARAM wp,
    LPARAM lp) {

    //今描画できてるやつ
    //ValidateRect(hWnd, NULL);
    //HDC hdc = m_prenderer.GetGlDC(hWnd);
    //m_prenderer.Render(hdc);


    switch (msg)
    {

        case WM_CLOSE:
        {
            int messageResult = MessageBox(hWnd, TEXT("Quit This?"), NULL, MB_OKCANCEL | MB_ICONWARNING);
            if (messageResult != IDOK) 
            {
                return 0;
            }
            else 
            {
                DefWindowProc(hWnd, msg, wp, lp);
            }
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;

        }
    }
    return DefWindowProc(hWnd, msg, wp, lp);
}

void CWindow::SetClientSize(HWND _hwnd, int width, int height)
{
    RECT window, client;
    GetWindowRect(_hwnd, &window);
    GetClientRect(_hwnd, &client);
    int newWidth = (window.right - window.left) - (client.right - client.left) + width;
    int newHeight = (window.bottom - window.top) - (client.bottom - client.top) + height;
    SetWindowPos(_hwnd,NULL, 0, 0, newWidth, newHeight, NULL);
}

HWND CWindow::GetHWND()
{
    return m_hwnd;
}
