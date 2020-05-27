#include "Mesh.h"
#include <windows.h>
#include "GL/glew.h"

GLuint CMesh::CreateShaderProgram() {
    //�o�[�e�b�N�X�V�F�[�_�[�R���p�C��
    GLuint vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexShader = R"#(
                                    attribute vec3 position;
                                    uniform mat4 MVP;
                                    void main(void){
                                    vec4 v = vec4(position, 1.0);
                                    gl_Position = MVP * v;
                                    }
                                )#";


    glShaderSource(vertShaderID, 1, &vertexShader, NULL);
    glCompileShader(vertShaderID);
    GLint success = 0;
    glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
    }

    //�t���O�����g�V�F�[�_�[�̃R���p�C��
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
    }

    //�v���O�����I�u�W�F�N�g�̍쐬
    GLuint m_programID = glCreateProgram();
    glAttachShader(m_programID, vertShaderID);
    glAttachShader(m_programID, fragShaderID);

    //�����N
    GLint linked;
    glLinkProgram(m_programID);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
    }


    glUseProgram(m_programID);

    m_uniformColor = glGetUniformLocation(m_programID, "color");
    if (m_uniformColor == -1) {
    }

    m_uniformModelMat = glGetUniformLocation(m_programID, "MVP");
    if (m_uniformModelMat) {

    }


    return m_programID;

}

GLint CMesh::CreateVAO(GLuint verticesCount, const GLfloat* position) {
    //���_�z��I�u�W�F�N�g
    m_vaoID = -1;
    glGenBuffers(1, &m_vaoID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, m_vaoID); // Bind our Vertex Buffer Object

    //���_�o�b�t�@�I�u�W�F�N�g
    m_vboID = -1;
    glGenBuffers(1, &m_vboID); // Generate our Vertex Buffer Object
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, verticesCount * 3 * sizeof(GLfloat), position, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW

    int attlocation = glGetAttribLocation(m_programID, "position");         //���Ԗڂ�attribute�ϐ���
    glEnableVertexAttribArray(attlocation);                                 //attribute������L���ɂ���
    glVertexAttribPointer(attlocation, 3, GL_FLOAT, GL_FALSE, 0, 0); //OpenGL����V�F�[�_�[�ɒ��_����

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return m_vaoID;
}
