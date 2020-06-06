#pragma once
#ifndef __MESH_H__
#define __MESH_H__
typedef unsigned int GLuint;
typedef int GLint;
typedef float GLfloat;

#include "glm/glm.hpp"


class CRenderer;
class CMesh {
	friend class CRenderer;
public:
	GLuint CreateShaderProgram(GLuint programID);
	GLint CreateVAO();

	void InitVertex();

	void SetColor(float r, float g, float b, float a);
	void SetLight(float x, float y, float z);
	GLuint GetVertexNum()const { return vertexNum; }
	glm::mat4 GetModelMatrix()const;
	const float* myvertices;
	glm::vec3 m_pos = glm::vec3(0, 0, 0);
	glm::vec3 m_rot = glm::vec3(0, 0, 0);
	glm::vec3 m_scale = glm::vec3(1, 1, 1);
private:

	glm::mat4 GetTransMatrix(glm::vec3 trans)const;
	glm::mat4 GetRotateMatrix(glm::vec3 rotate)const;
	glm::mat4 GetScaleMatrix(glm::vec3 scale)const;

	//float myvertices[18] = {
	//-0.5f , -0.5f ,0.0f, // Bottom left corner
	//-0.5f ,  0.5f ,0.0f, // Top left corner
	// 0.5f ,  0.5f ,0.0f, // Top Right corner    
	// 0.5f , -0.5f, 0.0f, // Bottom right corner
	//-0.5f , -0.5f, 0.0f, // Bottom left corner
	// 0.5f ,  0.5f, 0.0f, // Top Right corner 
	//};
	const float* m_normals;

	GLuint vertexNum = 0;

	GLuint m_programID = 0;

	GLint m_uniformColor = -1;
	GLint m_uniformModelMat = -1;
	GLint m_uniformLight = -1;

	GLuint m_vaoID = -1;
	GLuint m_vboID = -1;
	GLuint m_normalID = -1;
};

#endif