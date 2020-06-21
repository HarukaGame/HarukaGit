#pragma once
#ifndef __OBJECT_MANAGER_H__
#define __OBJECT_MANAGER_H__

#include "my_list.h"
#include "hash.h"
#include "glm/vec3.hpp"

class CGameObject;
class CRenderer;
class CMesh;
class CShader;

class CObjectManager {
public:
	bool Initilize();
	void Finalize();
	void AllObjectDraw(CRenderer* _renderer);
	CGameObject* CreateGameObject();
	CGameObject* CreateGameObject(const hash _hash);
	CGameObject* SearchGameObject(const hash _hash);
	CGameObject* SearchGameObject(const hash _hash,CList<CGameObject*>::iterator& _iter);
	void ZSort(const glm::vec3& _cameraPos);
	void DeleteObject(const hash _hash);
#ifdef _DEBUG
	void DebugShow();
#endif // _DEBUG

private:
	CList<CGameObject*> m_gameObjectList = CList<CGameObject*>();
};
#endif // !__OBJECT_MANAGER_H__
