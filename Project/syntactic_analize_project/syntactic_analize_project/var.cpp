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
