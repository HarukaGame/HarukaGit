#pragma once
#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "my_list.h"

enum class SORT_ORDER {
	SORT_ORDER_DESCENDING,
	SORT_ORDER_ASCENDING
};

enum class SORT_ATTRIBUTE {
	SORT_ATTRIBUTE_Z,
	SORT_ATTRIBUTE_DISTANCE
};

class CGameObject {
private:
	int m_layer = 0;
	float m_value = 0.0f;
	float m_z = 0.0f;
public:
	void SetLayer(const int _layer) { m_layer = _layer; };
	int GetLayer()const { return m_layer; };
	void SetValue(const float _value) { m_value = _value; };
	float GetValue()const {	return m_value;	};
	void SetZ(const float _z) { m_z = _z; };
	float GetZ()const { return m_z; };
};

class CObjectManager {
public:
	void Initilize();
	void Finalize();
	void LayerSort();
	void ZSort(const int _layer,const SORT_ATTRIBUTE _attribute,const SORT_ORDER _order);
	void Show();
private:
	bool CheckOrder(const CGameObject* _object1, const CGameObject* _object2, const SORT_ATTRIBUTE _attribute, const SORT_ORDER _order)const;
	CList<CGameObject*> m_objectList = CList<CGameObject*>();
};


#endif // !__OBJECT_MANAGER_H__
