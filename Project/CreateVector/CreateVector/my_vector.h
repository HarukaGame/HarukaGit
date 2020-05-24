#pragma once
//#include <iterator>
using namespace std;

template<class T>class MyVector;

template<class T> class MyVector {
private:
	T* buff;
	int buffSize;
public:
	explicit MyVector(int n) {
		buff = new T[n];
		buffSize = n;
	};
	~MyVector() {
		delete[] buff;
	};
	MyVector(const MyVector& v);
	MyVector& operator=(const MyVector& v);
	MyVector(MyVector&&);
	MyVector& operator=(MyVector&&);
	T& operator[](int);
	int Size()const;


	class MyIterator{
		MyVector* vec;
		int index;
	public:
		MyIterator(MyVector* v, int n) {
			vec = v;
			index = n;
		}
		//間接参照
		T& operator*() { return vec->buff[index]; }
		T* operator->() { return &vec->buff[index]; }
		//前置
		MyIterator& operator++() {
			index++;
			return *this;
		}
		MyIterator& operator--() {
			index--;
			return *this;
		}
		//後置
		MyIterator& operator++(int n) {
			MyIterator iter(*this);
			index++;
			return iter;
		}
		MyIterator& operator--(int n) {
			MyIterator iter(*this);
			index--;
			return iter;
		}
		//+= -=
		MyIterator& operator+=(int n) {
			index += n;
			return *this;
		}
		MyIterator& operator-=(int n) {
			index -= n;
			return *this;
		}
		//+ -
		MyIterator operator+(int n) {
			return MyIterator(vec, index + n);
		}
		MyIterator operator-(int n) {
			return MyIterator(vec, index - n);
		}
		//比較演算子
		bool operator==(const MyIterator& iter)const {
			return vec == iter.vec && index && iter.index;
		}
		bool operator!=(const MyIterator& iter)const {
			return vec != iter.vec || index != iter.index;
		}
		bool operator<(const MyIterator& iter)const {
			return vec == iter.vec && index < iter.index;
		}
		bool operator<=(const MyIterator& iter)const {
			return vec == iter.vec && index <= iter.index;
		}
		bool operator>(const MyIterator& iter)const {
			return vec == iter.vec && index > iter.index;
		}
		bool operator>=(const MyIterator& iter)const {
			return vec == iter.vec && index >= iter.index;
		}
	};
	MyIterator begin() {
		return MyIterator(this, 0);
	}
	MyIterator end() {
		return MyIterator(this, buffSize);
	}
};


//コピーコンストラクタ
template<class T>
MyVector<T>::MyVector(const MyVector<T>& v) {
	buff = new T[v.buffSize];
	buffSize = v.buffSize;
	for (int i = 0; i < buffSize; i++) {
		buff[i] = v.buff[i];
	}
}

//代入演算子
template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& v)
{
	if (this != &v) {
		if (buffSize != v.buffSize) {
			delete[] buff;
			buffSize = v.buffSize;
			buff = new T[buffSize];
		}
		for (int i = 0; i < buffSize; i++) {
			buff[i] = v.buff[i];
		}
	}
	return *this;
}

template<class T>
MyVector<T>::MyVector(MyVector&& v)
{
	buff = v.buff;
	buffSize = v.buffSize;
	v.buff = nullptr;
	v.buffSize = 0;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& v)
{
	if (this != &v) {
		delete[] buff;
		buff = v.buff;
		buffSize = v.buffSize;
		v.buff = nullptr;
		v.buffSize = 0;
	}
	return *this;
}

template<class T>
T& MyVector<T>::operator[](int i)
{
	if (i < 0 || i >= buffSize) {
		throw;
	}
	return buff[i];
}

template<class T>
int MyVector<T>::Size() const
{
	return buffSize;
}


