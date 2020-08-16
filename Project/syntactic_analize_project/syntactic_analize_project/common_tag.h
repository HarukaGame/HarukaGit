#pragma once
#ifndef __COMMON_TAG_H__
#define __COMMON_TAG_H__

#include "my_array.h"
#include "var.h"
#include "hash.h"


typedef const bool (TAG_FUNC)(CArray<CVar>* _varList, void* _pUserData);


struct TAG {
	TAG_FUNC* m_tagFunc = nullptr;
	hash m_hash = INVALID_HASH;
};


#endif // !__COMMON_TAG_H__
