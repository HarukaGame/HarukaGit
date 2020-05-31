#include "Mesh.h"
#include <windows.h>
#include "GL/glew.h"
#include <iostream>

#include "vertexfiles/cube.h"

GLuint CMesh::CreateShaderProgram(GLuint programID) {


    m_programID = programID;
    glUseProgram(m_programID);

    m_uniformColor = glGetUniformLocation(m_programID, "color");
    if (m_uniformColor == -1) {
        printf("color uniformの取得に失敗しました");

    }
    m_uniformLight = glGetUniformLocation(m_programID, "light");
    if (m_uniformLight == -1) {
        printf("light uniformの取得に失敗しました");

    }

    m_uniformModelMat = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformModelMat == -1) {
        printf("MVP uniformの取得に失敗しました");

    }




    return m_programID;

}

GLint CMesh::CreateVAO() {
    //頂点配列オブジェクト
    m_vaoID = -1;
    glGenBuffers(1, &m_vaoID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, m_vaoID); // Bind our Vertex Buffer Object

    //頂点バッファオブジェクト
    m_vboID = -1;
    glGenBuffers(1, &m_vboID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // Bind our Vertex Buffer Object

    glBufferData(GL_ARRAY_BUFFER, vertexNum * 2 * 3 * sizeof(GLfloat), &myvertices[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

    int attlocation = glGetAttribLocation(m_programID, "position");         //何番目のattribute変数か
    glEnableVertexAttribArray(attlocation);                                 //attribute属性を有効にする
    glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGLからシェーダーに頂点情報を



    m_normalID = -1;
    glGenBuffers(1, &m_normalID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, m_normalID); // Bind our Vertex Buffer Object



    glBufferData(GL_ARRAY_BUFFER, vertexNum * 3 * sizeof(GLfloat), &m_normals[0], GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    int normalLocation = glGetAttribLocation(m_programID, "normals");
    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_TRUE, 0,0);


    glBindBuffer(GL_ARRAY_BUFFER, attlocation);

    glBindBuffer(GL_ARRAY_BUFFER, normalLocation);

    
    glBindVertexArray(0);

    return m_vaoID;
}

void CMesh::InitVertex()
{
    myvertices = CUBE::verticex;
    m_normals = CUBE::normals;
    vertexNum = CUBE::vertexNum;
}

void CMesh::SetColor(float r, float g, float b, float a) {
    glUniform4f(m_uniformColor, r, g, b, a);
}

void CMesh::SetLight(float x, float y, float z)
{
    float length = sqrtf(x * x + y * y + z * z);
    glUniform3f(m_uniformLight, x/length, y/length, z/length);
}
