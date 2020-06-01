#pragma once

#ifndef __RAY_CAST_H__
#define __RAY_CAST_H__

#include "glm/glm.hpp"

class CMesh;

struct Ray {
	glm::vec3 m_origin = glm::vec3(0, 0, 0);
	glm::vec3 m_dirction = glm::vec3(0, 0, 0);
	Ray(glm::vec3 _origin, glm::vec3 _dir) {
		m_origin = _origin;
		m_dirction = _dir;
	}
};

struct RayCastHit {
	glm::vec3 m_point = glm::vec3(0, 0, 0);
	glm::vec3 m_normal = glm::vec3(0, 0, 0);
	float m_distance = 0;
};



class CRayCast {
public:
	static bool RayHitTriangle(const Ray& _ray,const float* _vertices);
	static bool RayHitTriangle(const Ray& _ray, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3);
	static bool RayHitTriangle(const Ray& _ray, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3, RayCastHit& rayCastHit);
	static bool RayHitMesh(const Ray& _ray, const CMesh* _mesh);
	static bool RayHitMesh(const Ray& _ray, const CMesh* _mesh,RayCastHit& rayCastHit);
};


#endif // !__RAY_CAST_H__
