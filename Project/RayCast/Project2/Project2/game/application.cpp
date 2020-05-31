#include "application.h"
#include "window.h"

bool CApplication::Initilize(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {
    m_pwindow = new CWindow();
    m_pwindow->WinInitilize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    return true;
}

void CApplication::Update(MSG* msg) {
    m_pwindow->DispUpdate();
}

void CApplication::Quit() {
    delete m_pwindow;
}