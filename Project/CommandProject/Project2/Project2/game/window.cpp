#include "window.h"
#include <iostream>
#include "GL/glew.h"
#include "GL/glut.h"
#include "device_input.h"

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


    AllocConsole();
    FILE* fp = NULL;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONIN$", "r", stdin);

    bool succses = GLSetUp();
    if (succses == false) {
        return false;
    }


    ShowWindow(m_hwnd, nCmdShow);

    UpdateWindow(m_hwnd);


    //CreateMesh();
    m_programID = CreateShader();
    return true;
}

GLuint CWindow::CreateShader() {
    //バーテックスシェーダーコンパイル
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexShader = R"#(
                                    attribute vec3 position;
                                    uniform mat4 MVP;
                                    void main(void){
                                    vec4 v = vec4(position, 1.0);
                                    gl_Position = MVP * v;
                                    }
                                )#";


    glShaderSource(vertShaderID, 1, &vertexShader,NULL);
    glCompileShader(vertShaderID);
    GLint success = 0;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        printf("バーテックスシェーダーのコンパイルに失敗しました\n");
    }

    //フラグメントシェーダーのコンパイル
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentShader = R"#(
                                    uniform vec4 color;
                                    void main(void){
                                    gl_FragColor = color;
                                    }
                                )#";
    glShaderSource(fragShaderID, 1, &fragmentShader, NULL);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        printf("フラグメントシェーダーのコンパイルに失敗しました\n");
    }

    //プログラムオブジェクトの作成
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);

    //リンク
    GLint linked;
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        printf("シェーダーのリンクに失敗しました");
    }


    glUseProgram(programID);

    uniform_color = glGetUniformLocation(programID, "color");
    if (uniform_color == -1) {
        printf("fadeユニフォームをバインドできませんでした");
    }

    uniform_modelMat = glGetUniformLocation(programID, "MVP");
    if (uniform_modelMat) {
        printf("MVPユニフォームをバインドできませんでした");

    }


    return programID;

}


bool CWindow::GLSetUp() {

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

    m_hdc = GetDC(m_hwnd);
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

void CWindow::GLRelease() {
    // 後処理
    // カレントコンテキストを無効にする
    wglMakeCurrent(NULL, NULL);

    // カレントコンテキストを削除
    wglDeleteContext(m_glrc);

    // デバイスコンテキスト解放
    ReleaseDC(m_hwnd, m_hdc);
}

void CWindow::DispUpdate() {
    wglMakeCurrent(m_hdc,m_glrc);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0);
    glUseProgram(m_programID);


    //--------------------------------
    angle += 0.01f;
    ObjectDisp(0.0f);

    //GLuint vaoID = -1;
    //GLuint vboID = -1;


    //glGenVertexArrays(1, &vaoID); // Create our Vertex Array Object
    //glBindVertexArray(vaoID); // Bind our Vertex Array Object so we can use it

    //float vertices[18] = {
    //    -0.5f , -0.5f ,0.0f, // Bottom left corner
    //    -0.5f ,  0.5f ,0.0f, // Top left corner
    //     0.5f ,  0.5f ,0.0f, // Top Right corner    
    //     0.5f , -0.5f, 0.0f, // Bottom right corner
    //    -0.5f , -0.5f, 0.0f, // Bottom left corner
    //     0.5f ,  0.5f, 0.0f, // Top Right corner 
    //};

    //glGenBuffers(1, &vboID); // Generate our Vertex Buffer Object
    //glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind our Vertex Buffer Object
    //glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW



    ////シェーダーチャレンジ
    ////色の変更
    //glUniform4f(uniform_color,1.0f, 0.0f, 1.0f, 0.5f);


    //angle += 0.01;
    ////行列の変更
    //GLfloat mvp[4][4] = {
    //    {cos(angle),-sin(angle)  ,0  ,0  },
    //    {sin(angle)  ,cos(angle),0  ,0  },
    //    {0  ,0  ,1,0  },
    //    {0  ,0  ,0  ,1  },
    //};
    //glUniformMatrix4fv(uniform_modelMat,1, GL_FALSE, &mvp[0][0]);



    //int attlocation = glGetAttribLocation(m_programID, "position");         //何番目のattribute変数か
    //glEnableVertexAttribArray(attlocation);                                 //attribute属性を有効にする
    //glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGLからシェーダーに頂点情報を

    //glBindVertexArray(vaoID); // Bind our Vertex Array Object

    //glDrawArrays(GL_TRIANGLES, 0, 6); // Draw our square

    //glDisableVertexAttribArray(attlocation);

    //glBindVertexArray(0); // Unbind our Vertex Array Object    glFlush();


    //--------------------------------



    SwapBuffers(m_hdc);
    glUseProgram(0);

    wglMakeCurrent(NULL, NULL);
}

void CWindow::ObjectDisp(float add) {

    GLuint vaoID = -1;
    //GLuint vboID = -1;
    float vertices[18] = {
    -0.5f+add , -0.5f ,0.0f, // Bottom left corner
    -0.5f+add ,  0.5f ,0.0f, // Top left corner
     0.5f+add ,  0.5f ,0.0f, // Top Right corner    
     0.5f+add , -0.5f, 0.0f, // Bottom right corner
    -0.5f+add , -0.5f, 0.0f, // Bottom left corner
     0.5f+add ,  0.5f, 0.0f, // Top Right corner 
    };

    vaoID = CreateVAO(6, vertices, m_programID);

    //glGenBuffers(1, &vboID); // Generate our Vertex Buffer Object
    //glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind our Vertex Buffer Object
    //glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW



    //シェーダーチャレンジ
    //glUniform1f(uniform_fade, 0.5f);
    //色の変更
    glUniform4f(uniform_color, 1.0f, 0.0f, 1.0f, 0.5f);



    //行列の変更
    GLfloat mvp[4][4] = {
        {cos(angle),-sin(angle)  ,0  ,0  },
        {sin(angle)  ,cos(angle),0  ,0  },
        {0  ,0  ,1,0  },
        {0  ,0  ,0  ,1  },
    };
    glUniformMatrix4fv(uniform_modelMat, 1, GL_FALSE, &mvp[0][0]);



    //int attlocation = glGetAttribLocation(m_programID, "position");         //何番目のattribute変数か
    //glEnableVertexAttribArray(attlocation);                                 //attribute属性を有効にする
    //glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGLからシェーダーに頂点情報を

    glBindVertexArray(vaoID); // Bind our Vertex Array Object

    glDrawArrays(GL_TRIANGLES, 0, 6); // Draw our square

    //glDisableVertexAttribArray(attlocation);

    //glBindVertexArray(0); // Unbind our Vertex Array Object    glFlush();

}

GLint CWindow::CreateVAO(GLuint verticesCount, const GLfloat* position, GLint program) {
    //頂点配列オブジェクト
    GLuint vaoID = -1;
    glGenBuffers(1, &vaoID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, vaoID); // Bind our Vertex Buffer Object

    GLuint vboID = -1;
    glGenBuffers(1, &vboID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, verticesCount * 3 * sizeof(GLfloat), position, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

    int attlocation = glGetAttribLocation(program, "position");         //何番目のattribute変数か
    glEnableVertexAttribArray(attlocation);                                 //attribute属性を有効にする
    glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGLからシェーダーに頂点情報を

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vaoID;
}

LRESULT CALLBACK CWindow::StaticWndProc(HWND hWnd,
    UINT msg,
    WPARAM wp,
    LPARAM lp) {


    int a;
    //今描画できてるやつ
    //ValidateRect(hWnd, NULL);
    //HDC hdc = m_prenderer.GetGlDC(hWnd);
    //m_prenderer.Render(hdc);

    switch (msg)
    {
        case WM_MOUSEWHEEL:
        {
            int wheelDelta = GET_WHEEL_DELTA_WPARAM(wp);
            int notch = wheelDelta / WHEEL_DELTA;
            CDeviceInput::SetMouseWheel((float)notch);
            return  DefWindowProc(hWnd, msg, wp, lp);
        }
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