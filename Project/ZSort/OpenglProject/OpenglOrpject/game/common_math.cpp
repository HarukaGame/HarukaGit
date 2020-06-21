#include "common_math.h"

namespace GLM_MATH_NAMESPACE {
	glm::mat4 GlmMath::Trans(const glm::vec3& _trans)
	{
		glm::mat4 ret = {
			1,
			0,
			0,
			0,

			0,
			1,
			0,
			0,

			0,
			0,
			1,
			0,

			_trans.x,
			_trans.y,
			_trans.z,
			1,

		};
		return ret;
	}

	glm::mat4 GlmMath::Rotate(const glm::vec3& _rotate)
	{
		return RotateX(_rotate.x)*RotateY(_rotate.y)*RotateZ(_rotate.z);
	}

	glm::mat4 GlmMath::Scale(const glm::vec3& _scale)
	{
		glm::mat4 ret = {
			_scale.x,
			0,
			0,
			0,

			0,
			_scale.y,
			0,
			0,

			0,
			0,
			_scale.z,
			0,

			0,
			0,
			0,
			1,

		};
		return ret;
	}

	glm::mat4 GlmMath::RotateX(const float _value)
	{
		glm::mat4 ret = {
			1,
			0,
			0,
			0,

			0,
			cosf(_value),
			sinf(_value),
			0,

			0,
			-sinf(_value),
			cosf(_value),
			0,

			0,
			0,
			0,
			1,

		};
		return ret;
	}

	glm::mat4 GlmMath::RotateY(const float _value)
	{
		glm::mat4 ret = {
			cosf(_value),
			0,
			sinf(_value),
			0,

			0,
			1,
			0,
			0,

			-sinf(_value),
			0,
			cosf(_value),
			0,

			0,
			0,
			0,
			1,

		};
		return ret;
	}

	glm::mat4 GlmMath::RotateZ(const float _value)
	{
		glm::mat4 ret = {
			cosf(_value),
			sinf(_value),
			0,
			0,

			-sinf(_value),
			cosf(_value),
			0,
			0,

			0,
			0,
			1,
			0,

			0,
			0,
			0,
			1,
		};
		return ret;
	}

	glm::mat4 GlmMath::ViewMatrix()
	{
		return glm::mat4();
	}

	glm::mat4 GlmMath::ProjectionMatrix(const float _angle, const float _aspect, const float _far, const float _near)
	{
		float zoomY = 1 / tanf(_angle / 2.0f);
		float zoomX = zoomY / _aspect;

		glm::mat4 ret = {
			zoomX,
			0,
			0,
			0,

			0,
			zoomY,
			0,
			0,

			0,
			0,
			(_far + _near) / (_far - _near),
			-1,

			0,
			0,
			-2.0f * _far * _near / (_far - _near),
			0
		};
		return ret;
	}

	glm::mat4 GlmMath::LookAt(const glm::vec3& _eye, const glm::vec3& _target, const glm::vec3& _up)
	{
		glm::vec3 cX = { 0.0,    0.0,    0.0 };
		glm::vec3 cY = { 0.0,    0.0,    0.0 };
		glm::vec3 cZ = { 0.0,    0.0,    0.0 };

		//カメラZ軸の設定
		cZ = glm::normalize(_eye - _target);

		//カメラX軸の設定
		cX = glm::normalize(glm::cross(_up, cZ));

		//カメラY軸の設定
		cY = glm::normalize(glm::cross(cZ, cX));


		////Z軸が手前にあるなら
		//if (inverseZ == true) {
		//	cZ = -cZ;
		//}
		float moveX = glm::dot(_eye, cX);
		float moveY = glm::dot(_eye, cY);
		float moveZ = glm::dot(_eye, cZ);
		glm::mat4 ret = {
			cX.x,
			cY.x,
			cZ.x,
			0,
			cX.y,
			cY.y,
			cZ.y,
			0,
			cX.z,
			cY.z,
			cZ.z,
			0,
			-moveX,
			-moveY,
			-moveZ,
			1
		};
		return ret;
	}


}

