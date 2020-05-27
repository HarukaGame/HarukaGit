#include "renderer.h"
#include "Mesh.h"
#include "GL/glew.h"
#include <cmath>


bool CRenderer::Initialize(HWND _hwnd) {
    m_hwnd = _hwnd;

    if (GLSetUp(_hwnd)) {
        return false;
    }

    return true;

}

void CRenderer::StartDisplay() {
    wglMakeCurrent(m_hdc, m_glrc);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);
}

void CRenderer::MeshDraw(const CMesh* _mesh) {
    glUseProgram(_mesh->m_programID);

    glUniform4f(_mesh->m_uniformColor, 1.0f, 0.0f, 0.0f, 1.0f);

    float angle = 0;
    GLfloat mvp[4][4] = {
    {cos(angle),-sin(angle)  ,0  ,0  },
    {sin(angle)  ,cos(angle),0  ,0  },
    {0  ,0  ,1,0  },
    {0  ,0  ,0  ,1  },
    };
    glUniformMatrix4fv(_mesh->m_uniformModelMat, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(_mesh->m_vaoID);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(0);
}

void CRenderer::EndDisplay() {
    SwapBuffers(m_hdc);
    wglMakeCurrent(NULL, NULL);

}

bool CRenderer::GLSetUp(HWND _hwnd){
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
        return false; // 該当するピクセルフォーマットが無い
    }

    // OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
    if (!SetPixelFormat(m_hdc, format, &pfd)) {
        return false; // DCへフォーマットを設定するのに失敗
    }

    // OpenGL contextを作成
    m_glrc = wglCreateContext(m_hdc);

    // 作成されたコンテキストがカレント（現在使用中のコンテキスト）か？
    if (!wglMakeCurrent(m_hdc, m_glrc)) {
        return false; // 何か正しくないみたい…
    }

    if (glewInit() != GLEW_OK) {
        return false;
    }
    return true;

}


void CRenderer::GLRelease() {
    // 後処理
    // カレントコンテキストを無効にする
    wglMakeCurrent(NULL, NULL);

    // カレントコンテキストを削除
    wglDeleteContext(m_glrc);

    // デバイスコンテキスト解放
    ReleaseDC(m_hwnd, m_hdc);
}


