#pragma once

#ifndef __BUFFER_H__
#define __BUFFER_H__
#include "GL/glew.h"
class CMesh;

class CBuffer {
public:
	int GetProgramID()const;
	void CreateBuffer(const CMesh* _mesh);
	int GetVertexNum()const;
private:
	GLuint m_buffer = 0;
	int m_vertexNum = 0;
};
#endif // !__BUFFER_H__
