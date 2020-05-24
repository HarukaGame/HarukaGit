#pragma once

#define START_SIZE 16

template<class T> 
class CVector {
public:
	///@brief	コンストラクタ
	CVector();
	///@brief	コピーコンストラクタ
	///@param[i]	_v	コピー元
	CVector(const CVector& _v);

	///@brief	ムーブコンストラクタ
	///@param[i]	_v	移動元
	CVector(CVector&& _v);

	///@brief	デストラクタ
	~CVector() {
		delete[] m_pBuff;
	};

	///@brief	代入演算子
	///@param[i]	_v		代入元
	///@return		CVector	代入先
	CVector& operator=(const CVector& _v);
	///@brief	代入演算子
	///@param[i]	_v	代入元
	///@return		CVector	代入先
	CVector& operator=(CVector&& _v);

	///@brief	配列添え字
	///@param[i]	_v	添え字
	///@return		T&	中身
	T& operator[](int _index);

	///@brief	要素数を取得
	///@return		s32	要素数
	int Size()const;

	///@brief	データ領域容量を取得
	///@return		s32	要素数
	int Capacity()const;

	///@brief	末尾に要素を追加する
	///@param[i]	_value	追加する要素
	void PushBack(T _value);

	///@brief	要素を挿入する
	///@param[i]	_value	挿入する要素
	///@param[i]	_num	挿入するインデックス
	///@return		b8		成功したかどうか
	bool Insert(T _value, int _num);

	///@brief	末尾の要素を削除する
	///@return		T	削除した要素
	T PopBack();

	///@brief	要素を削除するする
	///@param[i]	_num	削除するインデックス
	///@return		T		削除する要素
	T Erace(int _num);

	///@brief	イテレーターのクラス
	class MyIterator{
		CVector* m_pVec;
		int m_index;
	public:
		MyIterator(CVector* _v, int _n) {
			m_pVec = _v;
			m_index = _n;
		}
		//間接参照
		T& operator*() { return m_pVec->m_pBuff[m_index]; }
		T* operator->() { return &m_pVec->m_pBuff[m_index]; }
		//前置
		MyIterator& operator++() {
			m_index++;
			return *this;
		}
		MyIterator& operator--() {
			m_index--;
			return *this;
		}
		//後置
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
		//比較演算子
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

//コピーコンストラクタ
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



//代入演算子
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


