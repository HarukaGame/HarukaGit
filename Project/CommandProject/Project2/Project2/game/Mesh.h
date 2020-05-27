#pragma once
#ifndef __MESH_H__
#define __MESH_H__
typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;

class CRenderer;
class CMesh {
	friend class CRenderer;
public:
	GLuint CreateShaderProgram();
	GLint CreateVAO(GLuint verticesCount, const GLfloat* position);

private:
	GLuint m_programID = 0;

	GLint m_uniformColor = -1;
	GLint m_uniformModelMat = -1;

	GLuint m_vaoID = -1;
	GLuint m_vboID = -1;

};

#endif