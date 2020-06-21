#pragma once
#ifndef __SPHERE_CREATOR_H__
#define __SPHERE_CREATOR_H__


struct SphereInfo {
	int vertexNum = 0;
	int elementNum = 0;
	int dataNum = 0;
	float* vertices;
};

class CSphereCreator {
public:
	void CreateSphere(SphereInfo& _info,int _slice,int _cut);
};

#endif // !__SPHERE_CREATOR_H__
