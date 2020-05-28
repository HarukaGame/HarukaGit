#pragma once

#ifndef __MY_LIST_H__
#define __MY_LIST_H__

template<class T>
struct Node {
	T m_value;
	Node* m_pPrev = this;
	Node* m_pNext = this;
};
template<class T>
class CList {
public:


	CList();
	//CList(const CList& _v);
	//CList(CList&& _v);
	//~CList();
	

	//CList& operator=(const CList& _v);
	//Clist& operator=(CList&& _v);

	void PushFront(T _value);
	void PushBack(T _value);
	void Show();

	//int Length();
private:
	Node<T> dumm = { NULL,&dumm,&dumm };
	Node<T>* root = &dumm;
};

template<class T>
CList<T>::CList() {

}

template<class T>
void CList<T>::PushFront(T _value) {
	Node<T>* temp = new Node<T>();
	temp->m_value = _value;
	temp->m_pNext = root->m_pNext;
	temp->m_pPrev = root;
	root->m_pNext = temp;
	temp->m_pNext->m_pPrev = temp;
}

template<class T>
void CList<T>::PushBack(T _value)
{
	Node<T>* temp = new Node<T>();
	temp->m_value = _value;
	temp->m_pNext = root;
	temp->m_pPrev = root->m_pPrev;
	root->m_pPrev->m_pNext = temp;
	root->m_pPrev = temp;
}

template<class T>
void CList<T>::Show() {
	Node<T>* temp = root->m_pNext;
	while (temp != root) {
		printf("%d\n", temp->m_value);
		temp = temp->m_pNext;
	}
}

#endif // !__MY_LIST_H__
