#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include "hash.h"
#include "glm/matrix.hpp"

class CShader;
class CMesh;

class CGameObject {
public:
	void SetShader(const CShader* _shader);
	void SetMesh(const CMesh* _mesh);
	const CShader* GetShader()const;
	const CMesh* GetMesh()const;
	void SetPosition(const float _x,const float _y,const float _z);
	void SetRotate(const float _x, const float _y, const float _z);
	void SetScale(const float _x, const float _y, const float _z);
	glm::vec3 GetPosition()const;
	glm::mat4 GetTransMat();

	void SetHash(const hash _hash);
	hash GetHash()const;
	void Finalize();
	float distance = 0;
private:
	void ReCalculateTrans();

	const CMesh* m_pMesh = nullptr;
	const CShader* m_pShader = nullptr;
	hash m_hash = 0;

	glm::vec3 m_position = glm::vec3(0, 0, 0);
	glm::vec3 m_rotation = glm::vec3(0, 0, 0);
	glm::vec3 m_scale = glm::vec3(1, 1, 1);
	glm::mat4 m_trans = glm::mat4();
	bool m_moved = true;
};
#endif // !__GAMEOBJECT_H__
