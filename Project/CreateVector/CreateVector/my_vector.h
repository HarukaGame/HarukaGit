#pragma once
//#include <iterator>
//using namespace std;
#define START_SIZE 16

template<class T>class MyVector;

template<class T> class MyVector {
private:
	T* buff = nullptr;
	int buffCapacity = 0;
	int buffCount = 0;
public:
	explicit MyVector() {
		buff = new T[START_SIZE];
		buffCapacity = START_SIZE;
	};
	//explicit MyVector(int n) {
	//	buff = new T[n];
	//	buffSize = n;
	//};
	~MyVector() {
		delete[] buff;
	};
	MyVector(const MyVector& v);
	MyVector& operator=(const MyVector& v);
	MyVector(MyVector&&);
	MyVector& operator=(MyVector&&);
	T& operator[](int);
	int Size()const;
	int Capacity()const;
	void PushBack(T);
	bool Insert(T, int num);
	T PopBack();
	T Erace(int num);


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
		return MyIterator(this, buffCount);
	}

private:
	void BuffResize();
};


//コピーコンストラクタ
template<class T>
MyVector<T>::MyVector(const MyVector<T>& v) {
	buff = new T[v.buffCapacity];
	buffCapacity = v.buffCapacity;
	for (int i = 0; i < buffCapacity; i++) {
		buff[i] = v.buff[i];
	}
}

//代入演算子
template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& v)
{
	if (this != &v) {
		if (buffCapacity != v.buffCapacity) {
			delete[] buff;
			buffCapacity = v.buffCapacity;
			buff = new T[buffCapacity];
		}
		for (int i = 0; i < buffCapacity; i++) {
			buff[i] = v.buff[i];
		}
	}
	return *this;
}

template<class T>
MyVector<T>::MyVector(MyVector&& v)
{
	buff = v.buff;
	buffCapacity = v.buffCapacity;
	v.buff = nullptr;
	v.buffCapacity = 0;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& v)
{
	if (this != &v) {
		delete[] buff;
		buff = v.buff;
		buffCapacity = v.buffCapacity;
		v.buff = nullptr;
		v.buffCapacity = 0;
	}
	return *this;
}

template<class T>
T& MyVector<T>::operator[](int i)
{
	if (i < 0 || i >= buffCapacity) {
		throw;
	}
	return buff[i];
}

template<class T>
int MyVector<T>::Size() const
{
	return buffCapacity;
}

template<class T>
int MyVector<T>::Capacity() const
{
	return buffCapacity;
}

template<class T>
void MyVector<T>::PushBack(T value)
{
	if (buffCount == buffCapacity) {
		BuffResize();
	}
	buff[buffCount++] = value;
}

template<class T>
bool MyVector<T>::Insert(T value, int num)
{
	if (num < 0 || buffCount < num) {
		return false;
	}
	if (buffCount == buffCapacity) {
		BuffResize();
	}
	for (int i = buffCount; i > num; i--) {
		buff[i] = buff[i - 1];
	}
	buff[num] = value;
	buffCount++;
	return false;
}

template<class T>
T MyVector<T>::PopBack()
{
	if (buffCount == 0) {
		return nullptr;
	}
	T temp = buff[buffCount-1];
	buff[buffCount--] = nullptr;
	return temp;
}

template<class T>
T MyVector<T>::Erace(int num)
{
	T temp = buff[num];
	for (int i = num; i < buffCount-1; i++) {
		buff[i] = buff[i + 1];
	}
	buff[buffCount--] = nullptr;
	return temp;
}


template<class T>
void MyVector<T>::BuffResize()
{
	T* newBuff = new T[buffCapacity*2];
	for (int i = 0; i < buffCapacity; i++) {
		newBuff[i] = buff[i];
	}
	delete[] buff;
	buff = newBuff;
	buffCapacity *= 2;
}


