#include "lexical_analyzer.h"
#include "debug_print.h"

static const char CHAR_COMMA = ',';
static const char CHAR_SEMICOLON = ';';
static const char CHAR_UNDERBAR = '_';
static const char CHAR_NUMBER_START = '0';
static const char CHAR_NUMBER_END = '9';
static const char CHAR_SYNBOL_MINUS = '-';
static const char CHAR_SYNBOL_DOT = '.';
static const char CHAR_LOWER_CASE_LETTERS_START = 'a';
static const char CHAR_LOWER_CASE_LETTERS_END = 'z';
static const char CHAR_UPPER_CASE_LETTERS_START = 'A';
static const char CHAR_UPPER_CASE_LETTERS_END = 'Z';

bool CLexicalAnalizer::AnalizeLexical(const void* _buffer, unsigned int _length)
{
	unsigned int startIndex = 0;
	const char* charBuffer = static_cast<const char*>(_buffer);
	while (startIndex < _length) {
		AnalizelexicalLine(charBuffer, _length, startIndex);
		startIndex++;
	}
	return false;
}

bool CLexicalAnalizer::AnalizelexicalLine(const char* _buffer, unsigned int _length, unsigned int& _startIndex)
{
	if (_startIndex >= _length) {
		_startIndex = _length;
		return false;
	}

	unsigned int endIndex = SearchCharIndex(_buffer,_length,_startIndex, CHAR_SEMICOLON);
	if (endIndex == 0) {
		_startIndex++;
		return true;
	}

	for (unsigned int index = _startIndex; index <= endIndex; index++) {
		if (index > endIndex) {
			break;
		}
		if (IsFunctionChar(_buffer[index]) == true) {
			AnalizeFunction(_buffer, _length, index);
		}
	}
	_startIndex = endIndex+1;
	return true;
}

void CLexicalAnalizer::ShowToken()
{
	CList<TOKEN>::iterator iter = m_tokenList.Begin();
	CList<TOKEN>::iterator end = m_tokenList.End();
	for (; iter != end; iter++) {
		PRINT("%s\n", (*iter).m_var.GetCharData());
	}
}

unsigned int CLexicalAnalizer::SearchCharIndex(const char* _buffer, unsigned int _length, unsigned int _startIndex, char _char)
{
	if (_startIndex >= _length) {
		return 0;
	}
	unsigned int index = _startIndex;
	while (_buffer[index] != _char) {
		if (index >= _length) {
			return 0;
		}
		index++;
	}
	return index;
}

bool CLexicalAnalizer::AnalizeFunction(const char* _buffer, unsigned int _length, unsigned int& _startIndex)
{
	unsigned int index = _startIndex;
	while (IsFunctionChar(_buffer[index]) == true && index < _length) {
		index++;
	}

	TOKEN token;
	bool success =  CreateCharToken(token, TOKEN_TYPE::FUNCTION, _buffer, _length, _startIndex, index);
	if (success == true) {
		m_tokenList.PushBack(token);
	}
	_startIndex = index;
	return success;
}


bool CLexicalAnalizer::CreateCharToken(TOKEN& _token, TOKEN_TYPE _type, const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex)
{
	_token.m_tokenType = _type;
	unsigned int textLength = _endIndex - _startIndex;
	char* text = new char[textLength+1];
	if (text == nullptr) {
		return false;
	}


	for (unsigned int i = 0; i < textLength; i++) {
		text[i] = _buffer[_startIndex + i];
	}
	text[textLength] = '\0';

	_token.m_var.SetData(text);

	return true;
}

bool CLexicalAnalizer::IsFunctionChar(const char _char)
{
	if (CHAR_LOWER_CASE_LETTERS_START <= _char && _char <= CHAR_LOWER_CASE_LETTERS_END) {
		return true;
	}
	else if (CHAR_UPPER_CASE_LETTERS_START <= _char && _char <= CHAR_UPPER_CASE_LETTERS_END) {
		return true;
	}
	else if (_char == CHAR_UNDERBAR) {
		return true;
	}
	return false;
}

bool CLexicalAnalizer::IsNumberChar(const char _char)
{
	if (CHAR_NUMBER_START <= _char || _char <= CHAR_NUMBER_END) {
		return true;
	}
	else if(CHAR_SYNBOL_DOT == _char || CHAR_SYNBOL_MINUS == _char){
		return true;
	}
	return false;
}

bool CLexicalAnalizer::IsComma(const char _char)
{
	if (CHAR_COMMA == _char) {
		return true;
	}
	return false;
}

bool CLexicalAnalizer::IsSemicolon(const char _char)
{
	if (CHAR_SEMICOLON == _char) {
		return true;
	}
	return false;
}
