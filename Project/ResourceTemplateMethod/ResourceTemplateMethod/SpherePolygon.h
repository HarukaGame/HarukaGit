#pragma once
#include "ResourcePolygon.h"


class SpherePolygon :public ResourcePolygon<SpherePolygon> {
public:
	static int GetData();
};