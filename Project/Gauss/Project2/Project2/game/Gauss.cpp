#include "Gauss.h"

void SwapValue(float& a, float& b) {
	float temp = a;
	a = b;
	b = temp;
}

bool Gauss::CalcEquatons(glm::mat3& _a, glm::vec3& _b, glm::vec3& _solution)
{
	glm::mat3 tempMat = _a;
	_solution = _b;
	for (int i = 0; i < 3; i++) {
		int k = i;
		for (; k < 3 && tempMat[i][k] == 0; k++);
		if (k == 3) { return false; }
		if (i != k) {
			for (int swapCol = 0; swapCol < 3; swapCol++) {
				SwapValue(tempMat[swapCol][i], tempMat[swapCol][k]);
			}
			SwapValue(_solution[i], _solution[k]);
		}

		float temp = 1/tempMat[i][i];
		for (int s = 0; s < 3; s++) {
			if (i == s) {
				tempMat[s][i] = 1;
			}
			else {
				tempMat[s][i] *= temp;
			}
		}
		_solution[i] *= temp;
		for (int j = 0; j < 3; j++) {
			if (i != j) {
				float temp2 = tempMat[i][j];
				for (int Col = 0; Col < 3; Col++) {
					tempMat[Col][j] -= tempMat[Col][i] * temp2;
				}
				_solution[j] -= _solution[i] * temp2;
			}
		}
	}
	return true;
}
