#include "mesh.h"
#include "buffer.h"

#include <windows.h>
#include "GL/glew.h"
#include <iostream>

#include "vertexfiles/cube.h"

#include "common_math.h"
//GLuint CMesh::CreateShaderProgram(GLuint programID) {
//
//
//    m_programID = programID;
//    glUseProgram(m_programID);
//
//    m_uniformColor = glGetUniformLocation(m_programID, "color");
//    if (m_uniformColor == -1) {
//        printf("color uniformの取得に失敗しました");
//
//    }
//    m_uniformLight = glGetUniformLocation(m_programID, "light");
//    if (m_uniformLight == -1) {
//        printf("light uniformの取得に失敗しました");
//
//    }
//
//    m_uniformModelMat = glGetUniformLocation(m_programID, "MVP");
//    if (m_uniformModelMat == -1) {
//        printf("MVP uniformの取得に失敗しました");
//
//    }
//
//
//
//
//    return m_programID;
//
//}

//GLint CMesh::CreateVAO(){
//    //頂点配列オブジェクト
//    m_vaoID = -1;
//    glGenBuffers(1, &m_vaoID); // Generate our Vertex Buffer Object
//    glBindBuffer(GL_ARRAY_BUFFER, m_vaoID); // Bind our Vertex Buffer Object
//
//    //頂点バッファオブジェクト
//    m_vboID = -1;
//    glGenBuffers(1, &m_vboID); // Generate our Vertex Buffer Object
//    glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // Bind our Vertex Buffer Object
//
//    glBufferData(GL_ARRAY_BUFFER, vertexNum * 2 * 3 * sizeof(GLfloat), &myvertices[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
//
//    //int attlocation = glGetAttribLocation(m_programID, "position");         //何番目のattribute変数か
//    //glEnableVertexAttribArray(attlocation);                                 //attribute属性を有効にする
//    //glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGLからシェーダーに頂点情報を
//
//
//
//    //m_normalID = -1;
//    //glGenBuffers(1, &m_normalID); // Generate our Vertex Buffer Object
//    //glBindBuffer(GL_ARRAY_BUFFER, m_normalID); // Bind our Vertex Buffer Object
//
//
//
//    //glBufferData(GL_ARRAY_BUFFER, vertexNum * 3 * sizeof(GLfloat), &m_normals[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
//    //int normalLocation = glGetAttribLocation(m_programID, "normals");
//    //glEnableVertexAttribArray(normalLocation);
//    //glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_TRUE, 0,0);
//
//
//    //glBindBuffer(GL_ARRAY_BUFFER, attlocation);
//
//    //glBindBuffer(GL_ARRAY_BUFFER, normalLocation);
//
//    //
//    //glBindVertexArray(0);
//
//    return m_vaoID;
//}

void CMesh::InitVertex()
{
    myvertices = PolygonCube::verticex;
    m_normals = PolygonCube::normals;
    vertexNum = PolygonCube::vertexNum;
    elementNum = PolygonCube::elementNum;
}

//void CMesh::SetColor(float r, float g, float b, float a) {
//    glUniform4f(m_uniformColor, r, g, b, a);
//}
//
//void CMesh::SetLight(float x, float y, float z)
//{
//    float length = sqrtf(x * x + y * y + z * z);
//    glUniform3f(m_uniformLight, x/length, y/length, z/length);
//}



bool CMesh::CreateBuffer()
{
    m_pBuffer = new CBuffer();
    if (m_pBuffer == nullptr) {
        return false;
    }
    m_pBuffer->CreateBuffer(this);
    return false;
}

CBuffer* CMesh::GetBuffer() const
{
    return m_pBuffer;
}

glm::mat4 CMesh::GetModelMatrix() const
{
    glm::mat4 transMat = GetTransMatrix(m_pos);
    glm::mat4 rotateMat = GetRotateMatrix(m_rot);
    glm::mat4 scaleMat = GetScaleMatrix(m_scale);

    return transMat * rotateMat * scaleMat;
}

void CMesh::Finalize()
{
    if (m_pBuffer != nullptr) {
        m_pBuffer->DeleteBuffer();
        delete m_pBuffer;
    }
}

glm::mat4 CMesh::GetTransMatrix(glm::vec3 trans)const {
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


glm::mat4 CMesh::GetRotateMatrix(glm::vec3 rotate)const {
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
glm::mat4 CMesh::GetScaleMatrix(glm::vec3 scale)const {
    glm::mat4 scaleMat = {
    scale.x ,0      ,0      ,0,
    0       ,scale.y,0      ,0,
    0       ,0      ,scale.z,0,
    0       ,0      ,0      ,1
    };
    return scaleMat;
}