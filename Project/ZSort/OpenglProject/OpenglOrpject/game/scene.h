#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

class CObjectManager;
class CShader;
class CMesh;

#include "hash.h"
class CScene {
public:
	bool Initilize(CObjectManager* _objectManager);
	void Update();

	const CMesh* SearchOrCreateMesh(const hash _hash);
	const CShader* SearchOrCreateShader(const hash _hash);
private:
	CObjectManager* m_pObjectManager = nullptr;
};

#endif // !__SCENE_H__
