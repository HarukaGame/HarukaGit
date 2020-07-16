#pragma once

#ifndef __PREMIUM_LIB_H__
#define __PREMIIM_LIB_H__

namespace PREMIUM {
	template<class T,class U>
	static T SCast(const U _value) {
		return static_cast<T>(_value);
	}

	template<class T>
	static T PCast(void* _ptr) {
		return static_cast<T>(_ptr);
	}

	template<class T>
	static T CCast(const T _value) {
		return const_cast<T>(_value);
	}

}



#endif // !__PREMIUM_LIB_H__
