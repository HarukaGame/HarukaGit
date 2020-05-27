#include "application.h"
#include "window.h"
#include "device_input.h"
#include "command.h"
#include <iostream>

bool CApplication::Initilize(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) {
    m_pwindow = new CWindow();
    m_pwindow->WinInitilize(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

    CDeviceInput::CreateInstance();
    return true;
}

void CApplication::Update(MSG* msg) {
    m_pwindow->DispUpdate();
    CDeviceInput::DeviceInputUpdat();

    if (CComand::GetCommand(COMMAND_CAMERA_ROTATE)) {
        printf("COMMAND_CAMERA_ROTATE\n");
    }
    if (CComand::GetCommand(COMMAND_CAMERA_MOVE)) {
        printf("COMMAND_CAMERA_MOVE\n");
    }
    if (CComand::GetCommand(COMMAND_CAMERA_ZOOM)) {
        printf("COMMAND_CAMERA_ZOOM\n");
    }
    if (CComand::GetCommand(COMMAND_LIGHT_ROTATE)) {
        float h = CComand::GetAxis(COMMAND_HORIZONTAL);
        float v = CComand::GetAxis(COMMAND_VERTICAL);
        printf("%f       %f\n", h, v);
    }
    float wheel = CComand::GetAxis(COMMAND_WHEEL);
    printf("%f\n",wheel);


    CDeviceInput::DeviceInputRelease();
}

void CApplication::Quit() {
    m_pwindow->GLRelease();
    CDeviceInput::SafeDestory();
    delete m_pwindow;
}