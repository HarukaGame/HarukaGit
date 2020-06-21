#include "light.h"

CLight* CLight::s_instance = nullptr;

bool CLight::CreateInstance() {
	if (s_instance == nullptr) {
		s_instance = new CLight();
	}

	if (s_instance == nullptr) {
		return false;
	}

	return true;
}

void CLight::Destory() {
	if (s_instance != nullptr) {
		delete s_instance;
	}
}

CLight* CLight::GetInstance() {
	return s_instance;
}

glm::vec3 CLight::GetDirection() const
{
	return m_direction;
}

void CLight::SetRotate(const float _x, const float _z)
{
	m_angleAxisX = _x;
	m_angleAxisZ = _z;
	ReCalcDirection();
}

void CLight::Rotate(const float _x, const float _z)
{
	m_angleAxisX += _x;
	m_angleAxisZ += _z;
	ReCalcDirection();
}

void CLight::ReCalcDirection()
{
	float angleX = deg_to_rad(m_angleAxisX);
	float angleZ = deg_to_rad(m_angleAxisZ);
	m_direction.x = cosf(angleX) * sinf(angleZ);
	m_direction.y = sinf(angleX);
	m_direction.z = cosf(angleX) * cosf(angleZ);
}
