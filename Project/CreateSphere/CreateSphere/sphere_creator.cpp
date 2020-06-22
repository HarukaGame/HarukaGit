#include "sphere_creator.h"
#include <math.h>
#include <stdlib.h>

#define PI_MUL_2	6.28318530718f
#define PI			3.14159265359f
#define PI_DEV_2	1.57079632679f
#define PI_DEV_4	0.78539816330f

void CSphereCreator::CreateSphere(SphereInfo& _info, int _slice, int _cut)
{
	if (_slice < 1) {
		return;
	}
	if (_cut < 3) {
		return;
	}
	_info.vertexNum = (_slice * 6 + 6) * _cut;
	_info.elementNum = 6;
	_info.dataNum = _info.vertexNum * 2;
	//-------------------------------------------------------------------------------------
	//頂点の作成
	//-------------------------------------------------------------------------------------
	float* vertices = (float*)malloc(sizeof(float) * _info.vertexNum * 3);

	float angleX1 = 0;
	float angleX2 = 0;
	float angleY1 = (PI_DEV_2 - PI/(_slice+1));
	float angleY2 = 0;
	for (int c = 0; c < _cut; c++) {
		angleX1 = PI_MUL_2 * (float(c) / _cut);
		angleX2 = PI_MUL_2 * (float(c + 1) / _cut);

		vertices[c * 9] = 0.0f;
		vertices[c * 9 + 1] = 1.0f;
		vertices[c * 9 + 2] = 0.0f;

		vertices[c * 9 + 3] = cosf(angleY1) * sinf(angleX1);
		vertices[c * 9 + 4] = sinf(angleY1);
		vertices[c * 9 + 5] = cosf(angleY1) * cosf(angleX1);

		vertices[c * 9 + 6] = cosf(angleY1) * sinf(angleX2);
		vertices[c * 9 + 7] = sinf(angleY1);
		vertices[c * 9 + 8] = cosf(angleY1) * cosf(angleX2);
	}
	for (int s = 1; s < _slice; s++) {
		angleY1 = PI_DEV_2 - PI * ((float)s / (_slice+1));
		angleY2 = PI_DEV_2 - PI * ((float)(s+1) / (_slice+1));
		for (int c = 0; c < _cut; c++) {
			angleX1 = PI_MUL_2 * (float(c) / _cut);
			angleX2 = PI_MUL_2 * (float(c + 1) / _cut);

			vertices[c * 18 + _cut * 2 * (s-1) + _cut * 9 + 0] = cosf(angleY1) * sinf(angleX1);
			vertices[c * 18 + _cut * 2 * (s-1) + _cut * 9 + 1] = sinf(angleY1);
			vertices[c * 18 + _cut * 2 * (s-1) + _cut * 9 + 2] = cosf(angleY1) * cosf(angleX1);

			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 3] = cosf(angleY2) * sinf(angleX1);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 4] = sinf(angleY2);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 5] = cosf(angleY2) * cosf(angleX1);

			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 6] = cosf(angleY2) * sinf(angleX2);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 7] = sinf(angleY2);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 8] = cosf(angleY2) * cosf(angleX2);


			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 9] = cosf(angleY1) * sinf(angleX1);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 10] = sinf(angleY1);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 11] = cosf(angleY1) * cosf(angleX1);

			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 12] = cosf(angleY2) * sinf(angleX2);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 13] = sinf(angleY2);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 14] = cosf(angleY2) * cosf(angleX2);

			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 15] = cosf(angleY1) * sinf(angleX2);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 16] = sinf(angleY1);
			vertices[c * 18 + _cut * 2 * (s - 1) + _cut * 9 + 17] = cosf(angleY1) * cosf(angleX2);


		}
	}
	int slide = _cut * 9;
	_info.vertices = vertices;
}
