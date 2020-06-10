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

#define M_PI 3.14159265358979
#define deg_to_rad(deg) (((deg)/360)*2*M_PI)

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
        printf("GL�̃Z�b�g�A�b�v�Ɏ��s���܂���");
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
    //glClearDepth(0.0f);

    //glEnable(GL_DEPTH_TEST);

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearDepth(1.0f);



    glUseProgram(_mesh->m_programID);

    _mesh->CreateVAO();

    _mesh->SetColor(0, 1, 1, 1);
    _mesh->SetLight(1, 2, 3);

    test += 0.1f;


    glm::vec3 cameraPos = glm::vec3(5, 0, 5);


    glm::mat4 view = GetViewMatirix(
        cameraPos,
        glm::vec3(45, 0, 0)
    );

    glm::mat4 pro = GetProjectionMatrix(60, (float)WINDOW_WIDTH / WINDOW_HEIGHT, -1,1);


    //--------------------------------------------------------------------
    //���[���h���W����X�N���[�����W
    //--------------------------------------------------------------------
    glm::vec4 worldPosition = glm::vec4(test, test, 0, 1);
    glm::mat4 viewportMat = GetViewPortMatrix((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
    glm::vec4 screenPosition = viewportMat * pro * view * worldPosition;
    screenPosition /= screenPosition.w;
    //printf("test:%f     x:%f  y:%f  z:%f   z:%f\n", test,screenPosition.x, screenPosition.y, screenPosition.z, screenPosition.w);

    //--------------------------------------------------------------------
    //�X�N���[�����W���烏�[���h���W
    //--------------------------------------------------------------------
    POINT mouse = Input::GetMousePosition();
    glm::vec4 preScreenPos = glm::vec4(mouse.x, mouse.y, -1, 1);

    glm::mat4 inversePort = glm::inverse(viewportMat);
    glm::mat4 inverseProjection = glm::inverse(pro);
    glm::mat4 inverseView = glm::inverse(view);

    //�X�N���[�����[���h���W
    glm::vec4 toScreenWorldPos =inverseView * inverseProjection * inversePort * preScreenPos;
    glm::vec3 screenWorldPos3 = glm::vec3(toScreenWorldPos.x, toScreenWorldPos.y, toScreenWorldPos.z);
    //�C�ӂ̓_
    glm::vec3 floorPoint = glm::vec3(0, 0, -2);
    //�@��
    glm::vec3 normalVec = glm::vec3(0, 0, 1);

    glm::vec3 dir = screenWorldPos3 - cameraPos;

    glm::vec3 objectPos = CalcFloorPoint(cameraPos, dir, floorPoint, normalVec);
    //glm::vec3 objectPos = (glm::dot(normalVec, floorPoint - cameraPos) / glm::dot(normalVec, screenWorldPos3 - cameraPos)) * (screenWorldPos3 - cameraPos) + cameraPos;

    printf("test:%f     x:%f  y:%f  z:%f  w:%f   x:%f  y:%f  z:%f\n", 
                test, 
                toScreenWorldPos.x, 
                toScreenWorldPos.y, 
                toScreenWorldPos.z, 
                toScreenWorldPos.w, 
                objectPos.x,
                objectPos.y,
                objectPos.z
    );
    //----------------------------------
    glm::mat4 model = GetModelMatirix(
        glm::vec3(objectPos.x, objectPos.y, objectPos.z),
        glm::vec3(test, test, 0),
        glm::vec3(1, 1, 1)
    );


    glm::mat4 mvp =   pro * view * model;

    glm::vec4 pos = glm::vec4(1, 1, 1, 0);


    glUniformMatrix4fv(_mesh->m_uniformModelMat, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(_mesh->m_vaoID);

    glDrawArrays(GL_TRIANGLES, 0, _mesh->GetVertexNum());

    glUseProgram(0);
}

void CRenderer::EndDisplay() {
    SwapBuffers(m_hdc);
    wglMakeCurrent(NULL, NULL);

}

glm::vec3 CRenderer::CalcFloorPoint(glm::vec3 origin, glm::vec3 dir, glm::vec3 floor, glm::vec3 normal)
{
    return (glm::dot(normal, floor - origin) / glm::dot(normal, dir)) * dir + origin;
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
        printf("�s�N�Z���t�H�[�}�b�g�̑I���Ɏ��s���܂���");

        return false; // �Y������s�N�Z���t�H�[�}�b�g������
    }

    // OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
    if (!SetPixelFormat(m_hdc, format, &pfd)) {
        printf("�s�N�Z���t�H�[�}�b�g�̃Z�b�g�Ɏ��s���܂���");

        return false; // DC�փt�H�[�}�b�g��ݒ肷��̂Ɏ��s
    }

    // OpenGL context���쐬
    m_glrc = wglCreateContext(m_hdc);

    // �쐬���ꂽ�R���e�L�X�g���J�����g�i���ݎg�p���̃R���e�L�X�g�j���H
    if (!wglMakeCurrent(m_hdc, m_glrc)) {
        printf("�J�����g�R���e�L�X�g");

        return false; // �����������Ȃ��݂����c
    }

    if (glewInit() != GLEW_OK) {
        printf("GL�̏������Ɏ��s���܂���");

        return false;
    }
    return true;

}

void CRenderer::Release() {

    GLRelease();
}

bool CRenderer::SetShaderMesh(CMesh* mesh, const char* vert, const char* frag) {
    //�o�[�e�b�N�X�V�F�[�_�[�R���p�C��
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
        printf("�o�[�e�b�N�X�V�F�[�_�[�̃R���p�C���Ɏ��s���܂���");
    }

    //�t���O�����g�V�F�[�_�[�̃R���p�C��
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
        printf("�t���O�����g�V�F�[�_�[�̃R���p�C���Ɏ��s���܂���");

    }

    //�v���O�����I�u�W�F�N�g�̍쐬
    GLuint programID = glCreateProgram();
    if (programID == 0) {
        printf("�v���O�����I�u�W�F�N�g�̐����Ɏ��s���܂���");
    }
    glAttachShader(programID, vertShaderID);
    glAttachShader(programID, fragShaderID);
    GLint attached;
    glGetProgramiv(programID, GL_ATTACHED_SHADERS, &attached);
    if (attached == GL_FALSE) {
        printf("�V�F�[�_�[�̃A�^�b�`�Ɏ��s���܂���");

    }
    //�����N
    GLint linked;
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        printf("�V�F�[�_�[�̃����N�Ɏ��s���܂���");

    }
    mesh->CreateShaderProgram(programID);


    //mesh->m_programID = programID;

    return true;
}

//
//const char* CRenderer::ReadShaderCode(const char* filename,const char* code) {
//    //�t�@�C���̓ǂݍ���
//    std::ifstream ifs(filename);
//    if (!ifs)
//    {
//        printf("%s��ǂݍ��߂܂���ł���\n",filename);
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
    // �㏈��
    // �J�����g�R���e�L�X�g�𖳌��ɂ���
    wglMakeCurrent(NULL, NULL);

    // �J�����g�R���e�L�X�g���폜
    wglDeleteContext(m_glrc);

    // �f�o�C�X�R���e�L�X�g���
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

    //�J����Z���̐ݒ�
    cZ = glm::normalize(camera - target);

    //�J����X���̐ݒ�
    cX = glm::normalize(glm::cross(up, cZ));

    //�J����Y���̐ݒ�
    cY = glm::normalize(glm::cross(cZ,cX));


    //Z������O�ɂ���Ȃ�
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
    //glm::mat4 ret = {
    //    _width/2.0f,0,0,_width/2.0f,
    //    0,-_height/2.0f,0,_height/2.0f,
    //    0,0,1,0,
    //    0,0,0,1
    //};
    glm::mat4 ret = {
        _width/2.0f,0,0,0,
        0,-_height/2.0f,0,0,
        0,0,1,0,
        _width/2.0f,_height/2.0f,0,1
    };
    return ret;
}
