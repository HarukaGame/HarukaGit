
namespace PREMINUM {
	CVector2::CVector2() {
		x = 0;
		y = 0;
	}
	CVector2::CVector2(const float _x, const float _y) {
		x = _x;
		y = _y;
	}
	CVector2 CVector2::operator+(const CVector2& _vec)const {
		return CVector2(x + _vec.x, y + _vec.y);
	}
	CVector2 CVector2::operator-(const CVector2& _vec)const {
		return CVector2(x - _vec.x, y - _vec.y);
	}
	CVector2& CVector2::operator+=(const CVector2& _vec) {
		x += _vec.x;
		y += _vec.y;
		return *this;
	}
	CVector2& CVector2::operator-=(const CVector2& _vec) {
		x -= _vec.x;
		y -= _vec.y;
		return *this;
	}
	CVector2& CVector2::operator=(const CVector2& _vec) {
		x = _vec.x;
		y = _vec.y;
		return *this;
	}
	//CVector2 CVector2::operator*(const float _a)const {
	//	return CVector2(x * _a,y *_a);
	//}
	//CVector2 CVector2::operator/(const float _a)const {
	//	return CVector2(x / _a, y / _a);
	//}
	CVector2& CVector2::operator*=(const float _a) {
		x *= _a;
		y *= _a;
		return *this;
	}
	CVector2& CVector2::operator/=(const float _a) {
		x /= _a;
		y /= _a;
		return *this;
	}

	float Dot(const CVector2& _vec1, const CVector2& _vec2) {
		return _vec1.x * _vec2.x + _vec1.y * _vec2.y;
	}

	CVector2 operator*(const CVector2& _vec, const float _a){
		return CVector2(_vec.x * _a, _vec.y * _a);
	}
	CVector2 operator*(float _a, const CVector2& _vec){
		return CVector2(_vec.x * _a, _vec.y * _a);
	}

}


