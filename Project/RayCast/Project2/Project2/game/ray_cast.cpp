#include "ray_cast.h"
#include "Mesh.h"

bool CRayCast::RayHitTriangle(const Ray& _ray, const float* _vertice) {
	glm::vec3 edge1 = glm::vec3(_vertice[3] - _vertice[0],
								_vertice[4] - _vertice[1],
								_vertice[5] - _vertice[2]
								);
	glm::vec3 edge2 = glm::vec3(_vertice[6] - _vertice[0],
								_vertice[7] - _vertice[1],
								_vertice[8] - _vertice[2]
								);
	glm::vec3 fromOrigin = glm::vec3(	_ray.m_origin.x - _vertice[0],
										_ray.m_origin.y - _vertice[1],
										_ray.m_origin.z - _vertice[2] 
								);
	float determinU = glm::determinant(glm::mat3(	fromOrigin.x, edge2.x,_ray.m_dirction.x ,
													fromOrigin.y, edge2.y,_ray.m_dirction.y ,
													fromOrigin.z, edge2.z,_ray.m_dirction.z   ));
	float determinV = glm::determinant(glm::mat3(		edge1.x, fromOrigin.x, _ray.m_dirction.x,
														edge1.y, fromOrigin.y, _ray.m_dirction.y,
														edge1.z, fromOrigin.z, _ray.m_dirction.z));
	float determinT = glm::determinant(glm::mat3(		edge1.x, edge2.x, fromOrigin.x,
														edge1.y, edge2.y, fromOrigin.y,
														edge1.z, edge2.z, fromOrigin.z));

	float determinA = glm::determinant(glm::mat3(	 edge1.x, edge2.x,_ray.m_dirction.x,
													 edge1.y, edge2.y,_ray.m_dirction.y,
													 edge1.z, edge2.z,_ray.m_dirction.z ));
	float u = determinU/determinA;
	float v = determinV/determinA;
	float t = -determinT/determinA;
	printf("u:%f	v:%f	t:%f\n",u,v,t);

	bool hit =	u >= 0		&&
				v >= 0		&&
				0 <= u + v	&&
				u + v <= 1	&&
				t>0;
	if (hit == true) {
		int a = 0;
	}

	return	hit;

}

bool CRayCast::RayHitTriangle(const Ray& _ray, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3)
{
	RayCastHit temp;
	return RayHitTriangle(_ray, point1, point2, point3, temp);
}

bool CRayCast::RayHitTriangle(const Ray& _ray, const glm::vec3& point1, const glm::vec3& point2, const glm::vec3& point3, RayCastHit& rayCastHit)
{
	glm::vec3 edge1 = point2 - point1;
	glm::vec3 edge2 = point3 - point1;
	glm::vec3 fromOrigin = _ray.m_origin - point1;

	//列優先のため、下のコメントと同じような形で登録される
	glm::mat3 mat = glm::mat3(edge1,edge2,-_ray.m_dirction);
	//glm::mat3 mat = glm::mat3(
	//	edge1.x, edge2.x, -_ray.m_dirction.x,
	//	edge1.y, edge2.y, -_ray.m_dirction.y,
	//	edge1.z, edge2.z, -_ray.m_dirction.z
	//);
	glm::vec3 kai = glm::inverse(mat) * fromOrigin;

	float u = kai.x;
	float v = kai.y;
	float t = kai.z;
	float dot = glm::dot(_ray.m_dirction, glm::cross(edge2, edge1));
	//printf("u:%f	v:%f	t:%f\n", u, v, t);

	bool hit = u >= 0 &&
		v >= 0 &&
		0 <= u + v &&
		u + v <= 1 &&
		t > 0 &&
		dot > 0;
	if (hit == true) {
		glm::vec3 contactPoint = _ray.m_origin + t * _ray.m_dirction;
		float distance = glm::distance(contactPoint, _ray.m_origin);
		if (distance < rayCastHit.m_distance) {
			rayCastHit.m_point = contactPoint;
			rayCastHit.m_normal =  glm::normalize(glm::cross(edge1, edge2));
			rayCastHit.m_distance = distance;
		}
	}

	return	hit;
	//glm::vec3 edge1 = point2 - point1;
	//glm::vec3 edge2 = point3 - point1;
	//glm::vec3 fromOrigin = _ray.m_origin - point1;

	//float determinU = glm::determinant(glm::mat3(fromOrigin.x, edge2.x, _ray.m_dirction.x,
	//	fromOrigin.y, edge2.y, _ray.m_dirction.y,
	//	fromOrigin.z, edge2.z, _ray.m_dirction.z));
	//float determinV = glm::determinant(glm::mat3(edge1.x, fromOrigin.x, _ray.m_dirction.x,
	//	edge1.y, fromOrigin.y, _ray.m_dirction.y,
	//	edge1.z, fromOrigin.z, _ray.m_dirction.z));
	//float determinT = glm::determinant(glm::mat3(edge1.x, edge2.x, fromOrigin.x,
	//	edge1.y, edge2.y, fromOrigin.y,
	//	edge1.z, edge2.z, fromOrigin.z));
	//float determinA = glm::determinant(glm::mat3(edge1.x, edge2.x, _ray.m_dirction.x,
	//	edge1.y, edge2.y, _ray.m_dirction.y,
	//	edge1.z, edge2.z, _ray.m_dirction.z));
	//float u = determinU / determinA;
	//float v = determinV / determinA;
	//float t = -determinT / determinA;
	////printf("u:%f	v:%f	t:%f\n", u, v, t);
	//float dot = glm::dot(_ray.m_dirction, glm::cross(edge2, edge1));

	//bool hit = u >= 0 &&
	//	v >= 0 &&
	//	0 <= u + v &&
	//	u + v <= 1 &&
	//	t > 0 &&
	//	dot > 0;
	//if (hit == true) {
	//	rayCastHit.m_point = _ray.m_origin + t * _ray.m_dirction;
	//	rayCastHit.m_normal =  glm::normalize(glm::cross(edge1, edge2));
	//}

	//return	hit;
}

bool CRayCast::RayHitMesh(const Ray& _ray, const CMesh* _mesh)
{
	RayCastHit temp;
	return RayHitMesh(_ray, _mesh, temp);
}

bool CRayCast::RayHitMesh(const Ray& _ray, const CMesh* _mesh, RayCastHit& rayCastHit)
{
	bool hit = false;
	rayCastHit.m_distance = FLT_MAX;
	rayCastHit.m_normal = glm::vec3(0, 0, 0);
	rayCastHit.m_point = glm::vec3(0, 0, 0);
	int count = _mesh->GetVertexNum();
	for (int index = 0; index * 3 < count; index++) {
		glm::vec4 pos4[3] = {
			glm::vec4(_mesh->myvertices[index * 9 + 0], _mesh->myvertices[index * 9 + 1], _mesh->myvertices[index * 9 + 2], 1),
			glm::vec4(_mesh->myvertices[index * 9 + 3], _mesh->myvertices[index * 9 + 4], _mesh->myvertices[index * 9 + 5], 1),
			glm::vec4(_mesh->myvertices[index * 9 + 6], _mesh->myvertices[index * 9 + 7], _mesh->myvertices[index * 9 + 8], 1)
		};
		glm::vec3 pos3[3];
		for (int j = 0; j < 3; j++) {
			pos4[j] = _mesh->GetModelMatrix() * pos4[j];
			pos3[j] = glm::vec3(pos4[j].x, pos4[j].y, pos4[j].z);
		}
		hit |= RayHitTriangle(_ray, pos3[0], pos3[1], pos3[2],rayCastHit);
	}
	return hit;
}
