#pragma once
#ifndef __MY_ARRAY_H__
#define __MY_ARRAY_H__

template<class T>
class CArray {
public:
	bool Initialize(unsigned int _num);
	void Finalize();
	T* GetArray()const { return m_array; };
	unsigned int GetNum()const { return m_arrayNum; };
private:
	T* m_array = nullptr;
	unsigned int m_arrayNum = 0;
};


#endif // !__MY_ARRAY_H__

template<class T>
inline bool CArray<T>::Initialize(unsigned int _num)
{
	return false;
}

template<class T>
inline void CArray<T>::Finalize()
{
}
