#include "camera.h"
#include "common_math.h"

#define DISTANCE_START (5)
#define DISTANCE_MIN (5)
#define DISTANCE_MAX (30)

#define ANGLE_X_MAX (70)
#define ANGLE_X_MIN (-70)

CCamera* CCamera::s_mainCamera = nullptr;

using namespace GLM_MATH_NAMESPACE;

bool CCamera::CreateInstance(const float _width, const float _height)
{
	if (s_mainCamera == nullptr) {
		s_mainCamera = new CCamera();
	}
	if (s_mainCamera == nullptr) {
		return false;
	}
	s_mainCamera->m_width = _width;
	s_mainCamera->m_height = _height;
	s_mainCamera->CameraInitilize();
	return true;
}

CCamera* CCamera::GetInstance()
{
	return s_mainCamera;
}

void CCamera::Destroy()
{
	if (s_mainCamera != nullptr) {
		delete s_mainCamera;
	}
}

void CCamera::SetAngle(const float _axisX, const float _axisY)
{
	m_angleAxisX = _axisX;
	m_angleAxisY = _axisY;
	ReCalcTransform();
}

void CCamera::SetTargetPosition(const glm::vec3& _position)
{
	m_targetPosition = _position;
	ReCalcTransform();
}

void CCamera::Move(const glm::vec3& _move)
{
	m_targetPosition += _move;
	ReCalcTransform();
}

void CCamera::Rotate(const float _x, const float _y)
{
	m_angleAxisX += _x;
	m_angleAxisY += _y;
	if (m_angleAxisX > ANGLE_X_MAX) {
		m_angleAxisX = ANGLE_X_MAX;
	}else if (m_angleAxisX < ANGLE_X_MIN) {
		m_angleAxisX = ANGLE_X_MIN;
	}
	ReCalcTransform();
}

void CCamera::Zoom(const float _add)
{
	m_targetDistance += _add;
	ReCalcTransform();
}

glm::mat4 CCamera::GetViewMatrix() const
{
	return GlmMath::LookAt(m_position,m_targetPosition,glm::vec3(0,1,0) );
}

glm::mat4 CCamera::GetProjectionMatrix() const
{
	return GlmMath::ProjectionMatrix(deg_to_rad(60.0f),m_width/m_height,-1,1);
}

glm::vec3 CCamera::GetPosition() const
{
	return m_position;
}


void CCamera::ReCalcTransform()
{
	//角度をラジアン変換
	float radAngleX = deg_to_rad(m_angleAxisX);
	float radAngleZ = deg_to_rad(m_angleAxisY);
	//座標情報登録
	m_position.x = m_targetDistance * cosf(radAngleX)*sinf(radAngleZ);
	m_position.y = m_targetDistance * sinf(radAngleX);
	m_position.z = m_targetDistance * cosf(radAngleX) * cosf(radAngleZ);
	m_position += m_targetPosition;
	//回転情報登録
	m_rotation.x = m_angleAxisX;
	m_rotation.y = m_angleAxisY;
	m_rotation.z = 0;
	//姿勢行列登録
	m_transMat = GlmMath::Trans(m_position)* GlmMath::Rotate(m_rotation);
}

void CCamera::CameraInitilize()
{
	m_targetDistance = DISTANCE_START;
}
