#pragma once
#ifndef __LEXICAL_ANALIZER_H__
#define __LEXICAL_ANALIZER_H__

#include "var.h"
#include "my_list.h"

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

class CLexicalAnalizer {

public:
	bool AnalizeLexical(const void* _buffer,unsigned int _length);
	bool AnalizelexicalLine(const char* _buffer, unsigned int _length,unsigned int& _startIndex);
	void ShowToken();
	void Finalize();
private:
	static unsigned int SearchCharIndex(const char* _buffer, unsigned int _length, unsigned int _startIndex, char _char);
	static bool IsFunctionChar(const char _char);
	static bool IsNumberChar(const char _char);
	static bool IsComma(const char _char);
	static bool IsSemicolon(const char _char);
	static bool CheckIntToken(const char* _buffer, unsigned int _length, unsigned int _startIndex);
	static bool CheckFloatToken(const char* _buffer, unsigned int _length, unsigned int _startIndex);
	static int ConvertCharToInt(const char _char);

	bool AnalizeFunction(const char* _buffer, unsigned int _length, unsigned int& _startIndex);
	bool AnalizeNumber(const char* _buffer, unsigned int _length, unsigned int& _startIndex);
	bool AnalizeComma(const char* _buffer, unsigned int _length, unsigned int& _startIndex);
	bool CreateCharToken(TOKEN& _token,TOKEN_TYPE _type,const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex);
	bool CreateNumberToken(TOKEN& _token, TOKEN_TYPE _type, const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex);
	bool CreateCommaToken(TOKEN& _token, TOKEN_TYPE _type, const char* _buffer, unsigned int _length, unsigned int _startIndex);

	static bool SetIntVar(CVar& _var, const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex);
	static bool SetFloatVar(CVar& _var, const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex);
	
	CList<TOKEN> m_tokenList;
};


#endif // !__LEXICAL_ANALIZER_H__
