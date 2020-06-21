#pragma once
#ifndef __COMMON_MATH_H__
#define __COMMON_MATH_H__

#define M_PI 3.14159265358979f
#define deg_to_rad(deg) (((deg)/360.0f)*2.0f*M_PI)

#include "glm/matrix.hpp"

namespace GLM_MATH_NAMESPACE {
	class GlmMath {
	public:
		static glm::mat4 Trans(const glm::vec3& _trans);
		static glm::mat4 Rotate(const glm::vec3& _rotate);
		static glm::mat4 Scale(const glm::vec3& _scale);

		static glm::mat4 RotateX(const float _value);
		static glm::mat4 RotateY(const float _value);
		static glm::mat4 RotateZ(const float _value);


		static glm::mat4 ViewMatrix();
		static glm::mat4 ProjectionMatrix(const float _angle,const float _aspect,const float _far,const float _near);
		static glm::mat4 LookAt(const glm::vec3& _eye, const glm::vec3& _target, const glm::vec3& _up);
	};
};

#endif // !__COMMON_MATH_H__
