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
			SwapValue(tempMat[0][i], tempMat[0][k]);
			SwapValue(tempMat[1][i], tempMat[1][k]);
			SwapValue(tempMat[2][i], tempMat[2][k]);
			SwapValue(_solution[i], _solution[k]);
		}

		float temp = tempMat[i][i];
		tempMat[0][i] /= temp;
		tempMat[1][i] /= temp;
		tempMat[2][i] /= temp;
		_solution[i] /= temp;
		for (int j = 0; j < 3; j++) {
			if (i != j) {
				float temp2 = tempMat[i][j];
				tempMat[0][j] -= tempMat[0][i] * temp2;
				tempMat[1][j] -= tempMat[1][i] * temp2;
				tempMat[2][j] -= tempMat[2][i] * temp2;
				_solution[j] -= _solution[i] * temp2;
			}
		}
	}
	return true;
}
