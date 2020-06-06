#pragma once
#ifndef __GAUSS_H__
#define __GAUSS_H__
#include "glm/mat3x3.hpp"

class Gauss {
public:
	static bool CalcEquatons(glm::mat3& _a, glm::vec3& _b, glm::vec3& _solution);
};

#endif // __GAUSS_H__
