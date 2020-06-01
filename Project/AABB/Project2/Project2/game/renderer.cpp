#include "renderer.h"
#include "Mesh.h"
#include "GL/glew.h"
#include <cmath>

#include "fileloader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <math.h>
#include "input.h"

#include "ray_cast.h"

#include "common_math.h"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

float test = 0;

static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1,VERTEX = 0,FRAGMENT = 1 
    };

    std::string line;

    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}

bool CRenderer::Initialize(HWND _hwnd) {
    m_hwnd = _hwnd;

    if (GLSetUp(_hwnd) == false) {
        printf("GLのセットアップに失敗しました");
        return false;
    }

    return true;

}

void CRenderer::StartDisplay() {
    if (!wglMakeCurrent(m_hdc, m_glrc)) {
        printf("test");
    }
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glDepthRange(-1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    //glClearDepth(0.0f);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
}

void CRenderer::MeshDraw(CMesh* _mesh) {


    glUseProgram(_mesh->m_programID);

    _mesh->CreateVAO();

    _mesh->SetColor(0, 1, 1, 1);
    _mesh->SetLight(1, 2, 3);

    test += 0.1f;

    //カメラ座標の設定
    glm::vec3 cameraPos = glm::vec3(0, 5, 5);
    //モデル行列の取得
    glm::mat4 model = _mesh->GetModelMatrix();
    //ビュー行列の取得
    glm::mat4 view = GetViewMatirix(
        cameraPos,
        glm::vec3(45, 0, 0)
    );
    //プロジェクション行列の取得
    glm::mat4 pro = GetProjectionMatrix(60, (float)WINDOW_WIDTH / WINDOW_HEIGHT, -1, 1);

    //ビューポート行列の取得
    glm::mat4 viewportMat = GetViewPortMatrix((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

    //ビューポート行列の逆行列
    glm::mat4 inversePort = glm::inverse(viewportMat);
    //プロジェクション行列の逆行列
    glm::mat4 inverseProjection = glm::inverse(pro);
    //ビュー行列の逆行列
    glm::mat4 inverseView = glm::inverse(view);

    //マウス座標（スクリーン座標）
    POINT mouse = Input::GetMousePosition();
    //ベクトル４に登録（zは正規化デバイスの一番手前の値=`near）
    glm::vec4 preScreenPos = glm::vec4(mouse.x, mouse.y, -1, 1);

    //スクリーンのワールド座標上でのマウスの座標
    glm::vec4 toScreenWorldPos = inverseView * inverseProjection * inversePort * preScreenPos;
    glm::vec3 screenWorldPos3 = glm::vec3(toScreenWorldPos.x, toScreenWorldPos.y, toScreenWorldPos.z);
    
    //モデルの変数設定
    //_mesh->m_rot.x = test*10;
    //_mesh->m_rot.y = test*10;
    _mesh->m_rot.z = test*10;
    _mesh->m_scale.x = 5;

    //MVP行列の計算
    glm::mat4 mvp = pro * view * model;


    //レイの準備
    Ray ray = Ray(cameraPos, screenWorldPos3 - cameraPos);
    //あたったオブジェクトの情報を格納
    RayCastHit raycasthit;
    //当たったかどうか
    bool hit = CRayCast::RayHitMesh(ray, _mesh,raycasthit);
    if (hit) {
        printf("hit     point(X:%f    Y:%f    Z:%f)    normal(X:%f    Y:%f    Z:%f)\n",
            raycasthit.m_point.x, raycasthit.m_point.y, raycasthit.m_point.z,
            raycasthit.m_normal.x, raycasthit.m_normal.y, raycasthit.m_normal.z);
    }
    else {
        printf("none\n");
    }



    glUniformMatrix4fv(_mesh->m_uniformModelMat, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(_mesh->m_vaoID);

    glDrawArrays(GL_TRIANGLES, 0, _mesh->GetVertexNum());

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
        printf("ピクセルフォーマットの選択に失敗しました");

        return false; // 該当するピクセルフォーマットが無い
    }

    // OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
    if (!SetPixelFormat(m_hdc, format, &pfd)) {
        printf("ピクセルフォーマットのセットに失敗しました");

        return false; // DCへフォーマットを設定するのに失敗
    }

    // OpenGL contextを作成
    m_glrc = wglCreateContext(m_hdc);

    // 作成されたコンテキストがカレント（現在使用中のコンテキスト）か？
    if (!wglMakeCurrent(m_hdc, m_glrc)) {
        printf("カレントコンテキスト");

        return false; // 何か正しくないみたい…
    }

    if (glewInit() != GLEW_OK) {
        printf("GLの初期化に失敗しました");

        return false;
    }
    return true;

}

void CRenderer::Release() {

    GLRelease();
}

bool CRenderer::SetShaderMesh(CMesh* mesh, const char* vert, const char* frag) {
    //バーテックスシェーダーコンパイル
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);

    ShaderProgramSource ss = ParseShader("game/ShaderFiles/Basic.shader");
    const GLchar* vertexShader = ss.VertexSource.c_str();
    printf(vertexShader);
    //const char* vertexShader = 
    //CFileLoader::GetText("shader.vert", vertexShader);
    //const GLchar* vertexShader = R"#(
    //                                attribute vec3 position;
    //                                uniform mat4 MVP;
    //                                void main(void){
    //                                vec4 v = vec4(position, 1.0);
    //                                gl_Position = MVP * v;
    //                                }
    //                            )#";




    glShaderSource(vertShaderID, 1, &vertexShader, NULL);
    glCompileShader(vertShaderID);
    GLint success = 0;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        printf("バーテックスシェーダーのコンパイルに失敗しました");
    }

    //フラグメントシェーダーのコンパイル
    GLuint fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentShader = ss.FragmentSource.c_str();
    //ReadShaderCode(frag, fragmentShader);
    //const GLchar* fragmentShader = R"#(
    //                                uniform vec4 color;
    //                                void main(void){
    //                                gl_FragColor = color;
    //                                }
    //                            )#";
    glShaderSource(fragShaderID, 1, &fragmentShader, NULL);
    glCompileShader(fragShaderID);

    glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        printf("フラグメントシェーダーのコンパイルに失敗しました");

    }

    //プログラムオブジェクトの作成
    GLuint programID = glCreateProgram();
    if (programID == 0) {
        printf("プログラムオブジェクトの生成に失敗しました");
    }
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    GLint attached;
    glGetProgramiv(programID, GL_ATTACHED_SHADERS, &attached);
    if (attached == GL_FALSE) {
        printf("シェーダーのアタッチに失敗しました");

    }
    //リンク
    GLint linked;
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        printf("シェーダーのリンクに失敗しました");

    }
    mesh->CreateShaderProgram(programID);


    //mesh->m_programID = programID;

    return true;
}

//
//const char* CRenderer::ReadShaderCode(const char* filename,const char* code) {
//    //ファイルの読み込み
//    std::ifstream ifs(filename);
//    if (!ifs)
//    {
//        printf("%sを読み込めませんでした\n",filename);
//        return "";
//    }
//
//    std::string source;
//    std::string line;
//    while (getline(ifs, line))
//    {
//        source += line + "\n";
//    }
//
//    code = source.c_str();
//    std::cout << code << std::endl;
//    return code;
//}


void CRenderer::GLRelease() {
    // 後処理
    // カレントコンテキストを無効にする
    wglMakeCurrent(NULL, NULL);

    // カレントコンテキストを削除
    wglDeleteContext(m_glrc);

    // デバイスコンテキスト解放
    ReleaseDC(m_hwnd, m_hdc);
}

glm::mat4 CRenderer::GetTransMatrix(glm::vec3 trans) {
    //glm::mat4 transMat = {
    //1,0,0,trans.x,
    //0,1,0,trans.y,
    //0,0,1,trans.z,
    //0,0,0,1
    //};
    glm::mat4 transMat = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    trans.x,trans.y,trans.z,1
    };
    return transMat;
}
glm::mat4 CRenderer::GetRotateMatrix(glm::vec3 rotate) {
    rotate.x = deg_to_rad(rotate.x);
    rotate.y = deg_to_rad(rotate.y);
    rotate.z = deg_to_rad(rotate.z);
    glm::mat4 rotateX = {
    1,      0,      0,      0,
    0,      cos(rotate.x), -sin(rotate.x),0,
    0,      sin(rotate.x), cos(rotate.x), 0,
    0,      0,      0,      1
    };

    glm::mat4 rotateY = {
        cos(rotate.y), 0,      -sin(rotate.y),0,
        0,      1,      0 ,     0,
        sin(rotate.y), 0,      cos(rotate.y), 0,
        0,      0,      0,      1
    };

    glm::mat4 rotateZ = {
        cos(rotate.z), -sin(rotate.z),0,      0,
        sin(rotate.z), cos(rotate.z), 0,      0,
        0,      0,      1,      0,
        0,      0,      0,      1
    };
    glm::mat4 rotateMat = rotateX * rotateY * rotateZ;
    return rotateMat;
}
glm::mat4 CRenderer::GetScaleMatrix(glm::vec3 scale) {
    glm::mat4 scaleMat = {
    scale.x ,0      ,0      ,0,
    0       ,scale.y,0      ,0,
    0       ,0      ,scale.z,0,
    0       ,0      ,0      ,1
    };
    return scaleMat;
}


glm::mat4 CRenderer::GetModelMatirix(glm::vec3 trans, glm::vec3 rotate, glm::vec3 scale) {
    glm::mat4 transMat = GetTransMatrix(trans);
    glm::mat4 rotateMat = GetRotateMatrix(rotate);
    glm::mat4 scaleMat = GetScaleMatrix(scale);

    return transMat * rotateMat * scaleMat;
}


glm::mat4 CRenderer::GetViewMatirix(glm::vec3 camera, glm::vec3 target, glm::vec3 up, bool inverseZ) {
    glm::vec3 cX = { 0.0,    0.0,    0.0 };
    glm::vec3 cY = { 0.0,    0.0,    0.0 };
    glm::vec3 cZ = { 0.0,    0.0,    0.0 };

    //カメラZ軸の設定
    cZ = glm::normalize(camera - target);

    //カメラX軸の設定
    cX = glm::normalize(glm::cross(up, cZ));

    //カメラY軸の設定
    cY = glm::normalize(glm::cross(cZ,cX));


    //Z軸が手前にあるなら
    if (inverseZ == true) {
        cZ = -cZ;
    }
    float moveX = glm::dot(camera, cX);
    float moveY = glm::dot(camera, cY);
    float moveZ = glm::dot(camera, cZ);
    //float moveX = cZ.x;
    //float moveY = cZ.y;
    //float moveZ = cZ.z;

    //glm::mat4 ret = {
    //    cX.x    ,cY.x   ,cZ.x   ,0,
    //    cX.y    ,cY.y   ,cZ.y   ,0,
    //    cX.z    ,cY.z   ,cZ.z   ,0,
    //   -moveX       ,-moveY     ,-moveZ      ,1
    //};
    glm::mat4 ret = {
        cX.x    ,cX.y   ,cX.z   ,-moveX,
        cY.x    ,cY.y   ,cY.z   ,-moveY,
        cZ.x    ,cZ.y   ,cZ.z   ,-moveZ,
        0       ,0      ,0      ,1
    };
    //glm::mat4 ret = {
    //    cX.x    ,cY.x   ,cZ.x   ,-moveX,
    //    cX.y    ,cY.y   ,cZ.y   ,-moveY,
    //    cX.z    ,cY.z   ,cZ.z   ,-moveZ,
    //    0       ,0      ,0      ,1
    //};

    return ret;
}

glm::mat4 CRenderer::GetViewMatirix(glm::vec3 trans, glm::vec3 rotate) {
    
    return    GetRotateMatrix(-rotate)*GetTransMatrix(-trans);
}

glm::mat4 CRenderer::GetProjectionMatrix(float _angle, float _aspect, float _far, float _near) {
    float zoomY = 1 / tanf(deg_to_rad(_angle)/2.0f);
    float zoomX = zoomY / _aspect;

    glm::mat4 ret = {
        zoomX,0,0,0,
        0,zoomY,0,0,
        0,0,(_far+_near) / (_far - _near),-1,
        0,0,-2.0f*_far * _near / (_far - _near),0
    };
    return ret;
}

glm::mat4 CRenderer::GetViewPortMatrix(float _width, float _height)
{
    glm::mat4 ret = {
        _width/2.0f,    //size change
        0,
        0,
        0,

        0,
        -_height/2.0f,  //size change
        0,
        0,

        0,
        0,
        1,
        0,

        _width/2.0f,    //transform
        _height/2.0f,   //transform
        0,
        1
    };
    return ret;
}
