#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__


#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

class CCamera {
public:
	static bool CreateInstance(const float _width,const float _height);
	static CCamera* GetInstance();
	static void Destroy();

	void SetAngle(const float _axisX, const float _axisY);
	void SetTargetPosition(const glm::vec3& _position);
	void Move(const glm::vec3& _move);
	void Rotate(const float _x, const float _y);
	void Zoom(const float _add);

	glm::mat4 GetViewMatrix()const;
	glm::mat4 GetProjectionMatrix()const;
	glm::vec3 GetPosition()const;


private:
	void ReCalcTransform();
	void CameraInitilize();

	static CCamera* s_mainCamera;

	float m_width = 0;
	float m_height = 0;

	float m_angleAxisX = 0;
	float m_angleAxisY = 0;
	float m_targetDistance = 0;

	glm::vec3 m_targetPosition = glm::vec3(0,0,0);
	glm::vec3 m_position = glm::vec3(0,0,0);
	glm::vec3 m_rotation = glm::vec3(0,0,0);

	glm::mat4 m_transMat = glm::mat4();
};
#endif // !__CAMERA_H__
