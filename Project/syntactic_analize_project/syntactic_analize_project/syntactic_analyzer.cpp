#include "syntactic_analyzer.h"
#include "debug_print.h"

void CSyntacticAnalyzer::AddTag(hash _hash, TAG_FUNC* _tagFunc)
{
	if (_hash == INVALID_HASH) {
		PRINT("CSyntacticAnalyzer::AddTag _hash is INVALID");
		return;
	}

	TAG tag;
	tag.m_hash = _hash;
	tag.m_tagFunc = _tagFunc;
	m_tagList.PushBack(tag);
}

bool CSyntacticAnalyzer::AnalizeSyntactic(CList<TOKEN>* _tokenList)
{
	if (_tokenList == nullptr) {
		return false;
	}

	CList<TOKEN>::iterator end = _tokenList->End();

	CList<TOKEN>::iterator commmaIter = _tokenList->Begin();

	while (commmaIter != end) {
	}

	return false;
}

bool CSyntacticAnalyzer::AnalizeFunction(TAG_DATA& _tagData, CList<TOKEN>::iterator& startIter, CList<TOKEN>::iterator& endIter)
{
	if ((*startIter).m_tokenType != TOKEN_TYPE::FUNCTION) {
		return false;
	}
	
	_tagData.m_tag.m_hash = CHash::CRC32((*startIter).m_var.GetCharData());

	enum class TOKEN_STATE {
		NUMBER,
		COMMA,
	};

	TOKEN_STATE tokenState = TOKEN_STATE::NUMBER;

	CList<TOKEN>::iterator iter = startIter + 1;

	unsigned int numberCounter = 0;

	while (iter != endIter) {
		if (tokenState == TOKEN_STATE::NUMBER && (*iter).m_tokenType == TOKEN_TYPE::NUMBER) {
			tokenState = TOKEN_STATE::COMMA;
		}
		else if (tokenState == TOKEN_STATE::COMMA && (*iter).m_tokenType == TOKEN_TYPE::COMMA) {
			numberCounter++;
			tokenState = TOKEN_STATE::NUMBER;
		}
		else {
			return false;
		}
		iter++;
	}

	_tagData.m_varArray.Initialize(numberCounter);
	numberCounter = 0;
	iter = startIter + 1;
	while (iter != endIter) {
		if ((*iter).m_tokenType == TOKEN_TYPE::NUMBER) {
			_tagData.m_varArray[numberCounter] = (*iter).m_var;
			numberCounter++;
		}
		iter++;
	}

	return true;
}
