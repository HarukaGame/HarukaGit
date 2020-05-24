#pragma once

template<class T>
class ResourcePolygon {
public:
	static int GetData() { return T::GetData(); }
};

//class ResourcePolygon {
//public:
//	template<class T>
//	static int GetData() { return T::GetData(); }
//};