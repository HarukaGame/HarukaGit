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

    //bool succses = GLSetUp();
    //if (succses == false) {
    //    return false;
    //}

    m_prenderer = new CRenderer();
    if (m_prenderer == nullptr) {
        return false;
    }
    bool success = m_prenderer->Initialize(m_hwnd);
    if (success == false) {
        delete m_prenderer;
        return false;
    }


    ShowWindow(m_hwnd, nCmdShow);

    UpdateWindow(m_hwnd);

    testMesh = new CMesh();
    testMesh->InitVertex();
    m_prenderer->SetShaderMesh(testMesh, "shader.vert", "shader.frag");
    Input::CreateInstance();
    Input::SetWnd(m_hwnd);
    //CreateMesh();
    //m_programID = CreateShader();
    return true;
}




void CWindow::DispUpdate() {
    m_prenderer->StartDisplay();

    m_prenderer->MeshDraw(testMesh);

    m_prenderer->EndDisplay();
}

//void CWindow::ObjectDisp(float add) {
//
//    GLuint vaoID = -1;
//    //GLuint vboID = -1;
//    float vertices[18] = {
//    -0.5f+add , -0.5f ,0.0f, // Bottom left corner
//    -0.5f+add ,  0.5f ,0.0f, // Top left corner
//     0.5f+add ,  0.5f ,0.0f, // Top Right corner    
//     0.5f+add , -0.5f, 0.0f, // Bottom right corner
//    -0.5f+add , -0.5f, 0.0f, // Bottom left corner
//     0.5f+add ,  0.5f, 0.0f, // Top Right corner 
//    };
//
//    vaoID = CreateVAO(6, vertices, m_programID);
//
//    //glGenBuffers(1, &vboID); // Generate our Vertex Buffer Object
//    //glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind our Vertex Buffer Object
//    //glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
//
//
//
//    //シェーダーチャレンジ
//    //glUniform1f(uniform_fade, 0.5f);
//    //色の変更
//    glUniform4f(uniform_color, 1.0f, 0.0f, 1.0f, 0.5f);
//
//
//
//    //行列の変更
//    GLfloat mvp[4][4] = {
//        {cos(angle),-sin(angle)  ,0  ,0  },
//        {sin(angle)  ,cos(angle),0  ,0  },
//        {0  ,0  ,1,0  },
//        {0  ,0  ,0  ,1  },
//    };
//    glUniformMatrix4fv(uniform_modelMat, 1, GL_FALSE, &mvp[0][0]);
//
//
//
//    //int attlocation = glGetAttribLocation(m_programID, "position");         //何番目のattribute変数か
//    //glEnableVertexAttribArray(attlocation);                                 //attribute属性を有効にする
//    //glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGLからシェーダーに頂点情報を
//
//    glBindVertexArray(vaoID); // Bind our Vertex Array Object
//
//    glDrawArrays(GL_TRIANGLES, 0, 6); // Draw our square
//
//    //glDisableVertexAttribArray(attlocation);
//
//    //glBindVertexArray(0); // Unbind our Vertex Array Object    glFlush();
//
//}

//GLint CWindow::CreateVAO(GLuint verticesCount, const GLfloat* position, GLint program) {
//    //頂点配列オブジェクト
//    GLuint vaoID = -1;
//    glGenBuffers(1, &vaoID); // Generate our Vertex Buffer Object
//    glBindBuffer(GL_ARRAY_BUFFER, vaoID); // Bind our Vertex Buffer Object
//
//    GLuint vboID = -1;
//    glGenBuffers(1, &vboID); // Generate our Vertex Buffer Object
//    glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind our Vertex Buffer Object
//
//    glBufferData(GL_ARRAY_BUFFER, verticesCount * 3 * sizeof(GLfloat), position, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
//
//    int attlocation = glGetAttribLocation(program, "position");         //何番目のattribute変数か
//    glEnableVertexAttribArray(attlocation);                                 //attribute属性を有効にする
//    glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGLからシェーダーに頂点情報を
//
//    int normalLocation = glGetAttribLocation(program, "normals");
//    glEnableVertexAttribArray(normalLocation);
//    glVertexAttribPointer(normalLocation, 3, GL_FLAT, GL_TRUE, 0, 0);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//    return vaoID;
//}

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
