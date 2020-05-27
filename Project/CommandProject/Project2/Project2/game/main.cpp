#include "application.h"


int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    CApplication app;
    app.Initilize(hInstance,hPrevInstance,lpCmdLine,nCmdShow);

    MSG msg;


    while (true) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            app.Update(&msg);

        }
    }

    app.Quit();
    return 0;
}

