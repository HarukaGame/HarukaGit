#include "buffer.h"
#include "mesh.h"

int CBuffer::GetProgramID() const
{
	return m_buffer;
}

void CBuffer::CreateBuffer(const CMesh* _mesh)
{
	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, _mesh->GetVertexNum() * _mesh->GetElementNum() * sizeof(GLfloat), &_mesh->myvertices[0], GL_STATIC_DRAW);

	m_vertexNum = _mesh->GetVertexNum();
}

int CBuffer::GetVertexNum() const
{
	return m_vertexNum;
}
