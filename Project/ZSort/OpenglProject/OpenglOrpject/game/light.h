#pragma once
#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "common_math.h"

class CLight {
public:
	static bool CreateInstance();
	static void Destory();
	static CLight* GetInstance();
	glm::vec3 GetDirection()const;
	void SetRotate(const float _x, const float _z);
	void Rotate(const float _x, const float _z);
private:
	void ReCalcDirection();

	static CLight* s_instance;

	float m_angleAxisX = 0;
	float m_angleAxisZ = 0;
	glm::vec3 m_direction = glm::vec3(1, 0, 0);
};
#endif // !__LIGHT_H__
