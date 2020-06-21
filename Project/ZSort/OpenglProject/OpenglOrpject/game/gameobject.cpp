#include "gameobject.h"
#include "mesh.h"
#include "common_math.h"
using namespace GLM_MATH_NAMESPACE;


void CGameObject::SetShader(const CShader* _shader)
{
	m_pShader = _shader;
}

void CGameObject::SetMesh(const CMesh* _mesh)
{
	m_pMesh = _mesh;
}

const CShader* CGameObject::GetShader() const
{
	return m_pShader;
}

const CMesh* CGameObject::GetMesh() const
{
	return m_pMesh;
}

void CGameObject::SetPosition(const float _x, const float _y, const float _z)
{
	m_position = glm::vec3(_x, _y, _z);
	m_moved = true;
}

void CGameObject::SetRotate(const float _x, const float _y, const float _z)
{
	m_rotation = glm::vec3(_x, _y, _z);
	m_moved = true;
}

void CGameObject::SetScale(const float _x, const float _y, const float _z)
{
	m_scale = glm::vec3(_x, _y, _z);
	m_moved = true;
}

glm::vec3 CGameObject::GetPosition() const
{
	return m_position;;
}

glm::mat4 CGameObject::GetTransMat()
{
	if (m_moved == true) {
		ReCalculateTrans();
	}
	return m_trans;
}

void CGameObject::SetHash(const hash _hash)
{
	m_hash = _hash;
}

hash CGameObject::GetHash() const
{
	return m_hash;
}

void CGameObject::Finalize()
{

}

void CGameObject::ReCalculateTrans()
{
	m_trans = GlmMath::Trans(m_position) * GlmMath::Rotate(m_rotation) * GlmMath::Scale(m_scale);
}
