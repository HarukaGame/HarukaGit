#pragma once
#include "ResourcePolygon.h"

class CubePolygon :public ResourcePolygon<CubePolygon> {
public:
	static int GetData();
};