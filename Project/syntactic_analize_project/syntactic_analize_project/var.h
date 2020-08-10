#pragma once
#ifndef __VAR_H__
#define __VAR_H__

enum class VAR_TYPE {
	VAR_TYPE_INVALID,
	VAR_TYPE_STRING,
	VAR_TYPE_INT,
	VAR_TYPE_FLOAT
};

class CVar {
public:
	void SetData(const char* _value);
	void SetData(int _value);
	void SetData(float _value);
	const char* GetCharData()const { return m_data.m_str; };
	int GetIntData()const { return m_data.m_iData; };
	float GetFloatData()const { return m_data.m_fData; };
private:

	union DATA {
		const char* m_str = nullptr;
		int m_iData;
		float m_fData;
	};
	DATA m_data = DATA();
	VAR_TYPE m_tag = VAR_TYPE::VAR_TYPE_INVALID;
};

#endif // !__VAR_H__
