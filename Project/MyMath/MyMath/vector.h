#pragma once
#ifndef __VECTOR_H__
#define __VECTOR_H__
namespace PREMIUM {
	class CVector2 {
	public:
		CVector2();
		CVector2(const float _x, const float _y);

		CVector2 operator+(const CVector2& _vec)const;
		CVector2 operator-(const CVector2& _vec)const;
		CVector2& operator+=(const CVector2& _vec);
		CVector2& operator-=(const CVector2& _vec);
		CVector2& operator=(const CVector2& _vec);
		CVector2& operator*=(const float _a);
		CVector2& operator/=(const float _a);


		//メンバ変数
		float x = 0;
		float y = 0;
	};
	static float Dot(const CVector2& _vec1, const CVector2& _vec2);
	CVector2 operator*(const CVector2& _vec,float _a);
	CVector2 operator*(float _a, const CVector2& _vec);
}
#include "vector.inl"
#endif // !__VECTOR_H__
