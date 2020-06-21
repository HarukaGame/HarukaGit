#pragma once

#ifndef __MY_LIST_H__
#define __MY_LIST_H__


///@brief	ノードクラス
template<class T>
struct Node {
	T m_value;		//格納する値
	Node* m_pPrev = nullptr;//前のノードポインタ
	Node* m_pNext = nullptr;//後のノードポインタ

	///@brief	コンストラクタ
	Node() {
		m_pPrev = this;
		m_pNext = this;
	}
	///@brief	コンストラクタ
	///@param[in]	_value	格納する値
	///@param[in]	_prev	前のノードポインタ
	///@param[in]	_next	後のノードポインタ
	Node(T value, Node* prev, Node* next) {
		m_value = value;
		m_pPrev = prev;
		m_pNext = next;
	}
};


template<class T>
class CList {
public:
class CListIterator;

	///@brief	コンストラクタ
	CList();

	///@brief	コピーコンストラクタ
	///@param[in]	_list	
	CList(const CList& _list);

	///@brief	デストラクタ
	~CList();
	
	///@brief	代入演算子
	///@param[in]	_list
	///@return		CList
	CList& operator=(const CList& _list);

	///@brief	リストが空か判定
	///@return		bool	true:空
	bool Empty();

	///@brief	一番前に要素を入れる
	///@param[in]	_value
	void PushFront(T _value);

	///@brief	一番後ろに要素を入れる
	///@param[in]	_value
	void PushBack(T _value);

	void Insert(T _value, CListIterator _iter);

	///@brief	一番前の要素を取り出す
	///@return	T
	void PopFront();

	///@brief	一番後ろの要素を取り出す
	///@return	T
	void PopBack();

	void Pop(CListIterator _iter);

	///@brief	すべての要素を削除する
	void Clear();

	///@brief	持っている要素数を返す
	///@return	int	要素数
	int Length();
private:
	///@brief	要素を加える
	///@param[in]	_value
	///@param[in]	_node	加える位置の直前のノード
	void Add(T _value, Node<T>* _node);

	///@brief	ノードを削除する
	///@param[in]	_node	削除するノード
	///@return		T	削除するノードに入っていた要素
	void Remove(Node<T>* node);

	Node<T>* m_root = nullptr;	//環状リストのダミーノードポインタ
	int m_length = 0;			//ノードの数

public:
	///@brief	イテレータークラス
	class CListIterator {
	friend class CList;
	public:
		///@brief	コンストラクタ
		///@param[in]	_list	リストクラス	
		///@param[in]	_node	ノード
		CListIterator(CList* _list, Node<T>* _node) {
			m_pList = _list;
			m_pNode = _node;
		}

		///@brief	参照演算子
		///@return	T&		
		T& operator*() { return m_pNode->m_value; }

		///@brief	アロー演算子
		///@return	T*		
		T* operator->() { return &m_pNode->m_value; }

		///@brief	前置インクリメント
		///@return	CListIterator&
		CListIterator& operator++() {
			m_pNode = m_pNode->m_pNext;
		}

		///@brief	前置デクリメント
		///@return	CListIterator&
		CListIterator& operator--() {
			m_pNode = m_pNode->m_pPrev;
		}

		///@brief	後置インクリメント(引数はダミー)
		///@param[in]	_n	ダミー
		///@return	CListIterator&
		CListIterator& operator++(int n) {
			CListIterator iter(*this);
			m_pNode = m_pNode->m_pNext;
			return iter;
		}

		///@brief	後置デクリメント(引数はダミー)
		///@param[in]	_n	ダミー
		///@return	CListIterator&
		CListIterator& operator--(int n) {
			CListIterator iter(*this);
			m_pNode = m_pNode->m_pPrev;
			return iter;
		}

		///@brief	加算代入
		///@param[in]	_n	加算数
		///@return	CListIterator&
		CListIterator& operator+=(int n) {
			for (int i = 0; i < n; i++) {
				m_pNode = m_pNode->m_pNext;
			}
			return *this;
		}

		///@brief	減算代入
		///@param[in]	_n	減算数
		///@return	CListIterator&
		CListIterator& operator-=(int n) {
			for (int i = 0; i < n; i++) {
				m_pNode = m_pNode->m_pPrev;
			}
			return *this;
		}

		///@brief	加算
		///@param[in]	_n
		///@return	CListIterator
		CListIterator operator+(int n) {
			Node<T>* temp = m_pNode;
			for (int i = 0; i < n; i++) {
				temp = temp->m_pNext;
			}
			return CListIterator(m_pList, temp);
		}

		///@brief	減算
		///@param[in]	_n
		///@return	CListIterator
		CListIterator operator-(int n) {
			Node<T>* temp = m_pNode;
			for (int i = 0; i < n; i++) {
				temp = temp->m_pPrev;
			}
			return CListIterator(m_pList, temp);
		}

		///@brief	比較演算子	==
		///@param[in]	_iter
		///@return	T
		bool operator==(const CListIterator& _iter)const {
			return m_pList == _iter.m_pList && m_pNode == _iter.m_pNode;
		}

		///@brief	比較演算子	!=
		///@param[in]	_iter
		///@return	T
		bool operator!=(const CListIterator& _iter)const {
			return m_pList != _iter.m_pList || m_pNode != _iter.m_pNode;
		}

	private:
		CList* m_pList = nullptr;	//リストのポインタ
		Node<T>* m_pNode = nullptr;	//ノードのポインタ

	};

	///@brief	初めのイテレータを取得
	///@return	CListIterator
	CListIterator Begin() {
		return CListIterator(this, m_root->m_pNext);
	}

	///@brief	最後のイテレータを取得
	///@return	CListIterator
	CListIterator End() {
		return CListIterator(this, m_root);
	}
	typedef CListIterator iterator;

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
void CList<T>::Remove(Node<T>* node)
{
	if (Empty() == true) {
		return;
	}
	node->m_pPrev->m_pNext = node->m_pNext;
	node->m_pNext->m_pPrev = node->m_pPrev;
	delete node;
	m_length--;
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
inline void CList<T>::Insert(T _value, CListIterator _iter)
{
	Add(_value, _iter.m_pNode);
}

template<class T>
void CList<T>::PopFront() {
	Remove(m_root->m_pNext);
}


template<class T>
void CList<T>::PopBack() {
	Remove(m_root->m_pPrev);
}

template<class T>
void CList<T>::Pop(CListIterator _iter) {
	if (_iter == End()) {
		return;
	}
	Remove(_iter.m_pNode);
}

template<class T>
void CList<T>::Clear()
{
	while (Empty() == false) {
		PopBack();
	}
	m_length = 0;
}

template<class T>
int CList<T>::Length()
{
	return m_length;
}

#endif // !__MY_LIST_H__
