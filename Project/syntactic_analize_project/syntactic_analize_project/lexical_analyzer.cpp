#include "lexical_analyzer.h"
#include "debug_print.h"

static const char CHAR_COMMA = ',';
static const char CHAR_SEMICOLON = ';';
static const char CHAR_UNDERBAR = '_';
static const char CHAR_NUMBER_START = '0';
static const char CHAR_NUMBER_END = '9';
static const char CHAR_SYNBOL_MINUS = '-';
static const char CHAR_SYNBOL_DOT = '.';
static const char CHAR_SYNBOL_SLASH = '/';
static const char CHAR_SYNBOL_ENTER = 0x0A;
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

	unsigned int endIndex = SearchCharIndex(_buffer,_length,_startIndex, CHAR_SYNBOL_ENTER);
	if (endIndex == 0) {
		_startIndex++;
		return true;
	}
	unsigned int index = _startIndex;
	while (index <= endIndex) {
		if (index > endIndex) {
			break;
		}

		//"//"が来た場合、読み飛ばす
		if (index + 1 <= endIndex && _buffer[index] == CHAR_SYNBOL_SLASH && _buffer[index + 1] == CHAR_SYNBOL_SLASH) {
			break;
		}

		//タグが来た場合
		if (IsFunctionChar(_buffer[index]) == true) {
			AnalizeFunction(_buffer, _length, index);
		}
		else if (IsNumberChar(_buffer[index]) == true) {
			AnalizeNumber(_buffer, _length, index);
		}
		else if (IsComma(_buffer[index]) == true) {
			AnalizeComma(_buffer, _length, index);
		}
		else {
			index++;
		}
	}
	//for (unsigned int index = _startIndex; index <= endIndex; index++) {
	//	if (index > endIndex) {
	//		break;
	//	}

	//	//"//"が来た場合、読み飛ばす
	//	if (index + 1 <= endIndex && _buffer[index] == CHAR_SYNBOL_SLASH && _buffer[index + 1] == CHAR_SYNBOL_SLASH) {
	//		break;
	//	}

	//	//タグが来た場合
	//	if (IsFunctionChar(_buffer[index]) == true) {
	//		AnalizeFunction(_buffer, _length, index);
	//	}
	//	else if (IsNumberChar(_buffer[index]) == true) {
	//		AnalizeNumber(_buffer, _length, index);
	//	}
	//	else if (IsComma(_buffer[index]) == true) {
	//		AnalizeComma(_buffer, _length, index);
	//	}
	//	else {

	//	}
	//}
	_startIndex = endIndex;
	return true;
}

void CLexicalAnalizer::ShowToken()
{
	CList<TOKEN>::iterator iter = m_tokenList.Begin();
	CList<TOKEN>::iterator end = m_tokenList.End();
	for (; iter != end; iter++) {
		if ((*iter).m_tokenType == TOKEN_TYPE::FUNCTION) {
			PRINT("%s\n", (*iter).m_var.GetCharData());

		}
		else if ((*iter).m_tokenType == TOKEN_TYPE::NUMBER) {
			if ((*iter).m_var.GetVarType() == VAR_TYPE::VAR_TYPE_INT) {
				PRINT("%d\n", (*iter).m_var.GetIntData());

			}
			else if ((*iter).m_var.GetVarType() == VAR_TYPE::VAR_TYPE_FLOAT) {
				PRINT("%f\n", (*iter).m_var.GetFloatData());
			}

		}
		else if ((*iter).m_tokenType == TOKEN_TYPE::COMMA) {
			PRINT("%s\n", (*iter).m_var.GetCharData());
		}
	}
}

void CLexicalAnalizer::Finalize()
{
	CList<TOKEN>::iterator iter = m_tokenList.Begin();
	CList<TOKEN>::iterator end = m_tokenList.End();
	for (; iter != end; iter++) {
		if ((*iter).m_tokenType == TOKEN_TYPE::FUNCTION) {
			delete ((*iter).m_var.GetCharData());

		}
	}
	m_tokenList.Clear();
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

bool CLexicalAnalizer::AnalizeNumber(const char* _buffer, unsigned int _length, unsigned int& _startIndex)
{
	unsigned int index = _startIndex;
	while (IsNumberChar(_buffer[index]) == true && index < _length) {
		index++;
	}

	TOKEN token;
	bool success = CreateNumberToken(token, TOKEN_TYPE::NUMBER, _buffer, _length, _startIndex, index);
	if (success == true) {
		m_tokenList.PushBack(token);
	}
	_startIndex = index;
	return success;
}

bool CLexicalAnalizer::AnalizeComma(const char* _buffer, unsigned int _length, unsigned int& _startIndex)
{

	if (IsComma(_buffer[_startIndex]) == false) {
		return false;
	}

	TOKEN token;


	bool success = CreateCommaToken(token, TOKEN_TYPE::COMMA, _buffer, _length, _startIndex);
	if (success == true) {
		m_tokenList.PushBack(token);
	}
	_startIndex +=1;
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

bool CLexicalAnalizer::CreateNumberToken(TOKEN& _token, TOKEN_TYPE _type, const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex)
{
	_token.m_tokenType = _type;
	if (CheckIntToken(_buffer, _length, _startIndex)) {
		return SetIntVar(_token.m_var, _buffer, _length, _startIndex, _endIndex);
	}
	else if (CheckFloatToken(_buffer, _length, _startIndex)) {
		return SetFloatVar(_token.m_var, _buffer, _length, _startIndex, _endIndex);
	}
	return false;
}

bool CLexicalAnalizer::CreateCommaToken(TOKEN& _token, TOKEN_TYPE _type, const char* _buffer, unsigned int _length, unsigned int _startIndex)
{
	_token.m_tokenType = _type;
	char* text = new char[2];
	if (text == nullptr) {
		return false;
	}

	text[0] = _buffer[_startIndex];
	text[1] = '\0';

	_token.m_var.SetData(text);

	return true;
}

bool CLexicalAnalizer::SetIntVar(CVar& _var, const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex)
{
	bool minusFlag = false;
	if (_buffer[_startIndex] == CHAR_SYNBOL_MINUS) {
		minusFlag = true;
		_startIndex++;
	}

	int digit = 1;
	int tempIntValue = 0;
	for (unsigned int i = _endIndex; i >= _startIndex; i--) {
		if (_buffer[i] < CHAR_NUMBER_START || CHAR_NUMBER_END < _buffer[i]) {
			continue;
		}
		tempIntValue += ConvertCharToInt(_buffer[i]) * digit;
		digit *= 10;
	}

	if (minusFlag == true) {
		tempIntValue *= -1;
	}
	_var.SetData(tempIntValue);
	return true;
}

bool CLexicalAnalizer::SetFloatVar(CVar& _var, const char* _buffer, unsigned int _length, unsigned int _startIndex, unsigned int _endIndex)
{
	bool minusFlag = false;
	if (_buffer[_startIndex] == CHAR_SYNBOL_MINUS) {
		minusFlag = true;
		_startIndex++;
	}

	int digit = 1;
	int tempIntValue = 0;
	int dotDigit = 1;
	for (unsigned int i = _endIndex; i >= _startIndex; i--) {
		if (_buffer[i] == CHAR_SYNBOL_DOT) {
			dotDigit = digit;
		}
		if (_buffer[i] < CHAR_NUMBER_START || CHAR_NUMBER_END < _buffer[i]) {
			continue;
		}
		tempIntValue += ConvertCharToInt(_buffer[i]) * digit;
		digit *= 10;
	}

	float tempFloatValue = static_cast<float>(tempIntValue) / static_cast<float>(dotDigit);

	if (minusFlag == true) {
		tempFloatValue *= -1.0f;
	}
	_var.SetData(tempFloatValue);
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
	if (CHAR_NUMBER_START <= _char && _char <= CHAR_NUMBER_END) {
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

bool CLexicalAnalizer::CheckIntToken(const char* _buffer, unsigned int _length, unsigned int _startIndex)
{
	if (_startIndex >= _length) {
		return false;
	}
	unsigned int charCount = 0;
	unsigned int dotCount = 0;
	while (_startIndex + charCount < _length) {
		if (IsNumberChar(_buffer[_startIndex + charCount]) == false) {
			break;
		}
		if (_buffer[_startIndex + charCount] == CHAR_SYNBOL_DOT) {
			dotCount++;
		}
		charCount++;
	}

	if (dotCount == 0) {
		return true;
	}
	return false;
}

bool CLexicalAnalizer::CheckFloatToken(const char* _buffer, unsigned int _length, unsigned int _startIndex)
{
	if (_startIndex >= _length) {
		return false;
	}
	unsigned int charCount = 0;
	unsigned int dotCount = 0;
	while (_startIndex + charCount < _length) {
		if (IsNumberChar(_buffer[_startIndex + charCount]) == false) {
			break;
		}
		if (_buffer[_startIndex + charCount] == CHAR_SYNBOL_DOT) {
			dotCount++;
		}
		charCount++;
	}

	if (dotCount == 1) {
		return true;
	}
	return false;
}

int CLexicalAnalizer::ConvertCharToInt(const char _char)
{
	if (CHAR_NUMBER_START <= _char && _char <= CHAR_NUMBER_END) {
		return _char & 0x0f;
	}
	return -1;
}
