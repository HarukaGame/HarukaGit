#include "var.h"

void CVar::SetData(const char* _value)
{
	m_tag = VAR_TYPE::VAR_TYPE_STRING;
	m_data.m_str = _value;
}

void CVar::SetData(int _value)
{
	m_tag = VAR_TYPE::VAR_TYPE_INT;

	m_data.m_iData = _value;
}

void CVar::SetData(float _value)
{
	m_tag = VAR_TYPE::VAR_TYPE_FLOAT;
	m_data.m_fData = _value;
}

const char* CVar::GetCharData() const
{
	if (m_tag != VAR_TYPE::VAR_TYPE_STRING) {
		return nullptr;
	}
	return m_data.m_str;
}

int CVar::GetIntData() const
{
	if (m_tag == VAR_TYPE::VAR_TYPE_INT) {
		return m_data.m_iData;
	}
	else if (m_tag == VAR_TYPE::VAR_TYPE_FLOAT) {
		return static_cast<float>(m_data.m_iData);
	}
	return 0;
}

float CVar::GetFloatData() const
{
	if (m_tag == VAR_TYPE::VAR_TYPE_FLOAT) {
		return m_data.m_fData;
	}
	else if (m_tag == VAR_TYPE::VAR_TYPE_INT) {
		return static_cast<int>(m_data.m_fData);
	}
	return 0.0f;
}
