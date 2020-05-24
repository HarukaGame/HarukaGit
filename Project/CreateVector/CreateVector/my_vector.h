#pragma once

#define START_SIZE 16

template<class T> 
class CVector {
public:
	///@brief	�R���X�g���N�^
	CVector();
	///@brief	�R�s�[�R���X�g���N�^
	///@param[i]	_v	�R�s�[��
	CVector(const CVector& _v);

	///@brief	���[�u�R���X�g���N�^
	///@param[i]	_v	�ړ���
	CVector(CVector&& _v);

	///@brief	�f�X�g���N�^
	~CVector() {
		delete[] m_pBuff;
	};

	///@brief	������Z�q
	///@param[i]	_v		�����
	///@return		CVector	�����
	CVector& operator=(const CVector& _v);
	///@brief	������Z�q
	///@param[i]	_v	�����
	///@return		CVector	�����
	CVector& operator=(CVector&& _v);

	///@brief	�z��Y����
	///@param[i]	_v	�Y����
	///@return		T&	���g
	T& operator[](int _index);

	///@brief	�v�f�����擾
	///@return		s32	�v�f��
	int Size()const;

	///@brief	�f�[�^�̈�e�ʂ��擾
	///@return		s32	�v�f��
	int Capacity()const;

	///@brief	�����ɗv�f��ǉ�����
	///@param[i]	_value	�ǉ�����v�f
	void PushBack(T _value);

	///@brief	�v�f��}������
	///@param[i]	_value	�}������v�f
	///@param[i]	_num	�}������C���f�b�N�X
	///@return		b8		�����������ǂ���
	bool Insert(T _value, int _num);

	///@brief	�����̗v�f���폜����
	///@return		T	�폜�����v�f
	T PopBack();

	///@brief	�v�f���폜���邷��
	///@param[i]	_num	�폜����C���f�b�N�X
	///@return		T		�폜����v�f
	T Erace(int _num);

	///@brief	�C�e���[�^�[�̃N���X
	class MyIterator{
		CVector* m_pVec;
		int m_index;
	public:
		MyIterator(CVector* _v, int _n) {
			m_pVec = _v;
			m_index = _n;
		}
		//�ԐڎQ��
		T& operator*() { return m_pVec->m_pBuff[m_index]; }
		T* operator->() { return &m_pVec->m_pBuff[m_index]; }
		//�O�u
		MyIterator& operator++() {
			m_index++;
			return *this;
		}
		MyIterator& operator--() {
			m_index--;
			return *this;
		}
		//��u
		MyIterator& operator++(int _n) {
			MyIterator iter(*this);
			m_index++;
			return iter;
		}
		MyIterator& operator--(int _n) {
			MyIterator iter(*this);
			m_index--;
			return iter;
		}
		//+= -=
		MyIterator& operator+=(int _n) {
			m_index += _n;
			return *this;
		}
		MyIterator& operator-=(int _n) {
			m_index -= _n;
			return *this;
		}
		//+ -
		MyIterator operator+(int _n) {
			return MyIterator(m_pVec, m_index + _n);
		}
		MyIterator operator-(int _n) {
			return MyIterator(m_pVec, m_index - _n);
		}
		//��r���Z�q
		bool operator==(const MyIterator& _iter)const {
			return m_pVec == _iter.m_pVec && m_index && _iter.m_index;
		}
		bool operator!=(const MyIterator& _iter)const {
			return m_pVec != _iter.m_pVec || m_index != _iter.m_index;
		}
		bool operator<(const MyIterator& _iter)const {
			return m_pVec == _iter.m_pVec && m_index < _iter.m_index;
		}
		bool operator<=(const MyIterator& _iter)const {
			return m_pVec == _iter.m_pVec && m_index <= _iter.m_index;
		}
		bool operator>(const MyIterator& _iter)const {
			return m_pVec == _iter.m_pVec && m_index > _iter.m_index;
		}
		bool operator>=(const MyIterator& _iter)const {
			return m_pVec == _iter.m_pVec && m_index >= _iter.m_index;
		}
	};
	MyIterator begin() {
		return MyIterator(this, 0);
	}
	MyIterator end() {
		return MyIterator(this, m_buffCount);
	}
	typedef MyIterator iterator;

private:
	T* m_pBuff = nullptr;
	int m_buffCapacity = 0;
	int m_buffCount = 0;

	void BuffResizeDouble();
};


template<class T>
CVector<T>::CVector()
{
	m_pBuff = new T[START_SIZE];
	m_buffCapacity = START_SIZE;
}

//�R�s�[�R���X�g���N�^
template<class T>
CVector<T>::CVector(const CVector<T>& v) {
	m_pBuff = new T[v.m_buffCapacity];
	m_buffCapacity = v.m_buffCapacity;
	for (int i = 0; i < m_buffCapacity; i++) {
		m_pBuff[i] = v.m_pBuff[i];
	}
}

template<class T>
CVector<T>::CVector(CVector&& v)
{
	m_pBuff = v.m_pBuff;
	m_buffCapacity = v.m_buffCapacity;
	v.m_pBuff = nullptr;
	v.m_buffCapacity = 0;
}



//������Z�q
template<class T>
CVector<T>& CVector<T>::operator=(const CVector& v)
{
	if (this != &v) {
		if (m_buffCapacity != v.m_buffCapacity) {
			delete[] m_pBuff;
			m_buffCapacity = v.m_buffCapacity;
			m_pBuff = new T[m_buffCapacity];
		}
		for (int i = 0; i < m_buffCapacity; i++) {
			m_pBuff[i] = v.m_pBuff[i];
		}
	}
	return *this;
}



template<class T>
CVector<T>& CVector<T>::operator=(CVector&& v)
{
	if (this != &v) {
		delete[] m_pBuff;
		m_pBuff = v.m_pBuff;
		m_buffCapacity = v.m_buffCapacity;
		v.m_pBuff = nullptr;
		v.m_buffCapacity = 0;
	}
	return *this;
}

template<class T>
T& CVector<T>::operator[](int i)
{
	if (i < 0 || i >= m_buffCapacity) {
		throw;
	}
	return m_pBuff[i];
}

template<class T>
int CVector<T>::Size() const
{
	return m_buffCapacity;
}

template<class T>
int CVector<T>::Capacity() const
{
	return m_buffCapacity;
}

template<class T>
void CVector<T>::PushBack(T value)
{
	if (m_buffCount == m_buffCapacity) {
		BuffResizeDouble();
	}
	m_pBuff[m_buffCount++] = value;
}

template<class T>
bool CVector<T>::Insert(T value, int num)
{
	if (num < 0 || m_buffCount < num) {
		return false;
	}
	if (m_buffCount == m_buffCapacity) {
		BuffResizeDouble();
	}
	for (int i = m_buffCount; i > num; i--) {
		m_pBuff[i] = m_pBuff[i - 1];
	}
	m_pBuff[num] = value;
	m_buffCount++;
	return false;
}

template<class T>
T CVector<T>::PopBack()
{
	if (m_buffCount == 0) {
		return nullptr;
	}
	T temp = m_pBuff[m_buffCount-1];
	m_pBuff[m_buffCount--] = nullptr;
	return temp;
}

template<class T>
T CVector<T>::Erace(int num)
{
	T temp = m_pBuff[num];
	for (int i = num; i < m_buffCount-1; i++) {
		m_pBuff[i] = m_pBuff[i + 1];
	}
	m_pBuff[m_buffCount--] = nullptr;
	return temp;
}


template<class T>
void CVector<T>::BuffResizeDouble()
{
	T* newBuff = new T[m_buffCapacity*2];
	for (int i = 0; i < m_buffCapacity; i++) {
		newBuff[i] = m_pBuff[i];
	}
	delete[] m_pBuff;
	m_pBuff = newBuff;
	m_buffCapacity *= 2;
}


