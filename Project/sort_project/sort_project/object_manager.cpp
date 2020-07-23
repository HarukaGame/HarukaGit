#include "object_manager.h"
#include "debug_print.h"
#include <random>

void CObjectManager::Initilize() {
	std::random_device rnd;
	for (int i = 0; i < 100; i++) {
		CGameObject* tempGameObject = new CGameObject();
		int layer = rnd() % 2;
		float value = (rnd() % 100) / 1000.0f;
		float z = (rnd() % 100) / 1000.0f;
		tempGameObject->SetLayer(layer);
		tempGameObject->SetValue(value);
		tempGameObject->SetZ(z);
		m_objectList.PushBack(tempGameObject);
	}
}

void CObjectManager::Finalize()
{
	CList<CGameObject*>::iterator iter = m_objectList.Begin();
	CList<CGameObject*>::iterator end = m_objectList.End();
	for (; iter != end; iter++) {
		delete (*iter);
	}
	m_objectList.Clear();
}

void CObjectManager::LayerSort()
{
	if (m_objectList.Length() < 2) {
		return;
	}
	CList<CGameObject*>::iterator iter = m_objectList.Begin();
	CList<CGameObject*>::iterator end = m_objectList.End();
	iter++;
	for (; iter != end; iter++) {
		if ((*(iter - 1))->GetLayer() <= (*iter)->GetLayer()) {
			continue;
		}
		CList<CGameObject*>::iterator loopIter = iter-1;
		for (; loopIter != end; loopIter--) {
			if ((*loopIter)->GetLayer() <= (*iter)->GetLayer()) {
				break;
			}
		}


		CGameObject* tempObject = (*iter);
		CList<CGameObject*>::iterator tempIter = iter;
		iter--;
		m_objectList.Pop(tempIter);
		m_objectList.Insert(tempObject, loopIter);

		end = m_objectList.End();
	}
}

void CObjectManager::ZSort(const int _layer, const SORT_ATTRIBUTE _attribute, const SORT_ORDER _order)
{
	CList<CGameObject*>::iterator iter = m_objectList.Begin();
	CList<CGameObject*>::iterator end = m_objectList.End();
	CList<CGameObject*>::iterator layerStart = m_objectList.End();
	CList<CGameObject*>::iterator layerEnd = m_objectList.End();

	bool startFrag = false;
	unsigned int elementCount = 0;
	for (; iter != end; iter++) {
		if (startFrag == false && (*iter)->GetLayer() == _layer) {
			startFrag = true;
			layerStart = iter;
		}

		if (startFrag == true && (*iter)->GetLayer() != _layer) {
			layerEnd = iter;
			break;
		}

		if (startFrag == true) {
			elementCount++;
		}


	}

	if (elementCount < 2) {
		return;
	}
	CList<CGameObject*>::iterator elementIter = layerStart + 1;
	for (; elementIter != layerEnd; elementIter++) {
		if (CheckOrder(*(elementIter - 1), *elementIter,_attribute,_order)) {
			continue;
		}

		CList<CGameObject*>::iterator loopIter = elementIter - 1;

		for (; loopIter != layerStart - 1; loopIter--) {
			if (CheckOrder(*loopIter, *elementIter,_attribute,_order)) {
				break;
			}
		}

		bool isStart = loopIter == layerStart - 1;

		CGameObject* tempObejct = (*elementIter);
		CList<CGameObject*>::iterator tempIter = elementIter;
		elementIter--;
		m_objectList.Pop(tempIter);
		m_objectList.Insert(tempObejct, loopIter);

		if (isStart == true) {
			layerStart = loopIter+1;
		}

	}

}

void CObjectManager::Show() {
	CList<CGameObject*>::iterator iter = m_objectList.Begin();
	CList<CGameObject*>::iterator end = m_objectList.End();
	for (; iter != end; iter++) {
		PRINT("layer [%02d]  value[%0.3f]  z[%0.3f]\n", (*iter)->GetLayer(), (*iter)->GetValue(),(*iter)->GetZ());
	}
}

bool CObjectManager::CheckOrder(const CGameObject* _object1, const CGameObject* _object2, const SORT_ATTRIBUTE _attribute, const SORT_ORDER _order) const
{
	if (_attribute == SORT_ATTRIBUTE::SORT_ATTRIBUTE_Z) {
		if (_order == SORT_ORDER::SORT_ORDER_ASCENDING) {
			return _object1->GetZ() <= _object2->GetZ();
		}
		else if(_order == SORT_ORDER::SORT_ORDER_DESCENDING){
			return _object1->GetZ() >= _object2->GetZ();
		}
	}
	else {
		if (_order == SORT_ORDER::SORT_ORDER_ASCENDING) {
			return _object1->GetValue() <= _object2->GetValue();
		}
		else if (_order == SORT_ORDER::SORT_ORDER_DESCENDING) {
			return _object1->GetValue() >= _object2->GetValue();
		}
	}
	return false;
}

