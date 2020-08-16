#pragma once
#ifndef __SYNTACTIC_ANALYZER_H__
#define __SYNTACTIC_ANALYZER_H__

#include "common_tag.h"
#include "my_array.h"
#include "my_list.h"
#include "var.h"
#include "common_analize.h"
#include "hash.h"

struct TAG_DATA {
	TAG m_tag;
	CArray<CVar> m_varArray;
	const bool Invoke(void* _pUserData) {
		return m_tag.m_tagFunc(&m_varArray, _pUserData);
	}
};

class CSyntacticAnalyzer {
public:
	void AddTag(hash _hash, TAG_FUNC* _tagFunc);
	bool AnalizeSyntactic(CList<TOKEN>* _tokenList);
private:

	static bool AnalizeFunction(TAG_DATA& _tagData,CList<TOKEN>::iterator& startIter, CList<TOKEN>::iterator& endIter);
	CList<TAG_DATA> m_tagDataList;
	CList<TAG> m_tagList;
};

#endif // !__SYNTACTIC_ANALYZER_H__
