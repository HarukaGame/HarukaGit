#pragma once
#ifndef __LEXICAL_ANALIZER_H__
#define __LEXICAL_ANALIZER_H__

#include "var.h"

enum class TOKEN_TYPE {
	INVALID,
	FUNCTION,
	SEMICOLON,
	COMMA,

};

struct TOKEN {
	CVar m_var;
	TOKEN_TYPE m_tokenType = TOKEN_TYPE::INVALID;

};

class CLexicalAnalizer {
private:
};


#endif // !__LEXICAL_ANALIZER_H__
