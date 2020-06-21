#include "opengl_device.h"
#include "GL/glew.h"
#include "debug_print.h"

bool COpenglDevice::Initilize(HWND _hwnd)
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
        PFD_TYPE_RGBA,                                              //The kind of framebuffer. RGBA or palette.
        32,                                                         //Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                                                         //Number of bits for the depthbuffer
        8,                                                          //Number of bits for the stencilbuffer
        0,                                                          //Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    m_hdc = GetDC(_hwnd);
    int format = ChoosePixelFormat(m_hdc, &pfd);
    if (format == 0) {
        PRINT("ピクセルフォーマットの選択に失敗しました");

        return false; // 該当するピクセルフォーマットが無い
    }

    // OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
    if (!SetPixelFormat(m_hdc, format, &pfd)) {
        PRINT("ピクセルフォーマットのセットに失敗しました");

        return false; // DCへフォーマットを設定するのに失敗
    }

    // OpenGL contextを作成
    m_glrc = wglCreateContext(m_hdc);

    // 作成されたコンテキストがカレント（現在使用中のコンテキスト）か？
    if (!wglMakeCurrent(m_hdc, m_glrc)) {
        PRINT("カレントコンテキスト");

        return false; // 何か正しくないみたい…
    }

    if (glewInit() != GLEW_OK) {
        PRINT("GLの初期化に失敗しました");

        return false;
    }
    return true;

}

void COpenglDevice::SwapBuffer()
{
    SwapBuffers(m_hdc);

}

void COpenglDevice::Finalize()
{
    // 後処理
// カレントコンテキストを無効にする
    wglMakeCurrent(NULL, NULL);

    // カレントコンテキストを削除
    wglDeleteContext(m_glrc);

    // デバイスコンテキスト解放
    ReleaseDC(m_hwnd, m_hdc);
}
