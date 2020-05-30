#pragma once

#ifndef __MY_LIST_H__
#define __MY_LIST_H__

///@brief	ÉmÅ[ÉhÉNÉâÉX
template<class T>
struct Node {
	T m_value = NULL;		//
	Node* m_pPrev = nullptr;//
	Node* m_pNext = nullptr;//

	///@brief
	Node() {
		m_value = NULL;
		m_pPrev = this;
		m_pNext = this;
	}
	///@brief
	///@param[in]
	///@param[in]
	///@param[in]
	Node(T value, Node* prev, Node* next) {
		m_value = value;
		m_pPrev = prev;
		m_pNext = next;
	}
};
template<class T>
class CList {
public:

	///@brief
	CList();

	///@brief
	///@param[in]	_list
	CList(const CList& _list);

	///@brief
	~CList();
	
	///@brief
	///@param[in]	_list
	///@return		CList
	CList& operator=(const CList& _list);

	///@brief
	///@param[in]	_list
	///@return		CList
	bool Empty();
	///@brief
	///@param[in]	_value
	void PushFront(T _value);
	///@brief
	///@param[in]	_value
	void PushBack(T _value);
	///@brief
	///@return		T
	T PopFront();
	///@brief
	///@return		T
	T PopBack();
	///@brief
	void Clear();
	///@brief
	///@return		int
	int Length();
private:
	///@brief
	///@param[in]	_value
	///@param[in]	_node
	void Add(T _value, Node<T>* _node);
	///@brief
	///@param[in]	_node
	///@return		T
	T Remove(Node<T>* node);

	Node<T>* m_root = nullptr;	//
	int m_length = 0;			//

public:
	///@brief
	class MyIterator {
	public:
		///@brief
		///@param[in]	_value
		///@param[in]	_node
		MyIterator(CList* _v, Node<T>* _node) {
			m_pList = _v;
			m_pNode = _node;
		}
		//MyIterator(CList* _v, Node<T>* _node) {
		//	m_pList = _v;
		//	m_pNode = _node;
		//}
		///@brief
		///@return	T
		T& operator*() { return m_pNode->m_value; }

		///@brief
		///@return	T
		T* operator->() { return &m_pNode->m_value; }
		///@brief
		///@return	T
		MyIterator& operator++() {
			m_pNode = m_pNode->m_pNext;
		}
		///@brief
		///@return	T
		MyIterator& operator--() {
			m_pNode = m_pNode->m_pPrev;
		}
		///@brief
		///@param[in]	_value
		///@return	T
		MyIterator& operator++(int n) {
			MyIterator iter(*this);
			m_pNode = m_pNode->m_pNext;
			return iter;
		}
		///@brief
		///@param[in]	_value
		///@return	T
		MyIterator& operator--(int n) {
			MyIterator iter(*this);
			m_pNode = m_pNode->m_pPrev;
			return iter;
		}
		///@brief
		///@param[in]	_value
		///@return	T
		MyIterator& operator+=(int n) {
			for (int i = 0; i < n; i++) {
				m_pNode = m_pNode->m_pNext;
			}
			return *this;
		}
		///@brief
		///@param[in]	_value
		///@return	T
		MyIterator& operator-=(int n) {
			for (int i = 0; i < n; i++) {
				m_pNode = m_pNode->m_pPrev;
			}
			return *this;
		}
		///@brief
		///@param[in]	_value
		///@return	T
		MyIterator operator+(int n) {
			Node<T>* temp = m_pNode;
			for (int i = 0; i < n; i++) {
				temp = temp->m_pNext;
			}
			return MyIterator(m_pList, temp);
		}
		///@brief
		///@param[in]	_value
		///@return	T
		MyIterator operator-(int n) {
			Node<T>* temp = m_pNode;
			for (int i = 0; i < n; i++) {
				temp = temp->m_pPrev;
			}
			return MyIterator(m_pList, temp);
		}
		//î‰ärââéZéq
		bool operator==(const MyIterator& _iter)const {
			return m_pList == _iter.m_pList && m_pNode == _iter.m_pNode;
		}
		bool operator!=(const MyIterator& _iter)const {
			return m_pList != _iter.m_pList || m_pNode != _iter.m_pNode;
		}

	private:
		CList* m_pList = nullptr;
		Node<T>* m_pNode = nullptr;

	};
	MyIterator Begin() {
		return MyIterator(this, m_root->m_pNext);
	}
	MyIterator End() {
		return MyIterator(this, m_root);
	}
	typedef MyIterator iterator;

};

template<class T>
CList<T>::CList() {
	m_root = new Node<T>();
}

template<class T>
CList<T>::CList(const CList& _v)
{
	m_root = new Node<T>();
	Node<T>* temp = _v.m_root->m_pNext;
	while (temp != _v.m_root) {
		PushBack(temp->m_value);
		temp = temp->m_pNext;
	}
}

template<class T>
inline CList<T>::~CList()
{
	Clear();
	delete m_root;
}

template<class T>
CList<T>& CList<T>::operator=(const CList& _v)
{
	if (this != &_v) {
		Clear();
		Node<T>* temp = _v.m_root->m_pNext;
		while (temp != _v.m_root) {
			PushBack(temp->m_value);
			temp = temp->m_pNext;
		}
	}
	return *this;
}

template<class T>
bool CList<T>::Empty()
{
	return m_root->m_pNext == m_root;
}

template<class T>
void CList<T>::Add(T _value, Node<T>* _node)
{
	if (_node == nullptr) {
		return;
	}
	Node<T>* newNode = new Node<T>(_value, _node, _node->m_pNext);
	newNode->m_pNext->m_pPrev = newNode;
	newNode->m_pPrev->m_pNext = newNode;
	m_length++;
}

template<class T>
T CList<T>::Remove(Node<T>* node)
{
	if (Empty() == true) {
		throw;
	}
	T ret = node->m_value;
	node->m_pPrev->m_pNext = node->m_pNext;
	node->m_pNext->m_pPrev = node->m_pPrev;
	delete node;
	m_length--;
	return ret;
}

template<class T>
void CList<T>::PushFront(T _value) {
	Add(_value, m_root);
}

template<class T>
void CList<T>::PushBack(T _value)
{
	Add(_value, m_root->m_pPrev);
}

template<class T>
T CList<T>::PopFront() {
	return Remove(m_root->m_pNext);
}


template<class T>
T CList<T>::PopBack() {
	return Remove(m_root->m_pPrev);
}

template<class T>
inline void CList<T>::Clear()
{
	while (Empty() == false) {
		PopBack();
	}
	m_length = 0;
}

template<class T>
inline int CList<T>::Length()
{
	return m_length;
}

#endif // !__MY_LIST_H__
