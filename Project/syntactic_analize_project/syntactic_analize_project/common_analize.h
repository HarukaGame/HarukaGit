#pragma once
#ifndef __COMMON_ANALIZE_H__
#define __COMMON_ANALIZE_H__

#include "var.h"

enum class TOKEN_TYPE {
	INVALID,
	FUNCTION,
	NUMBER,
	COMMA,
	SEMICOLON,
};

struct TOKEN {
	CVar m_var;
	TOKEN_TYPE m_tokenType = TOKEN_TYPE::INVALID;

};


#endif // !__COMMON_ANALIZE_H__



