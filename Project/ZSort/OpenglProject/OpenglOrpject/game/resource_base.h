#pragma once

#ifndef __RESOURCE_BASE_H__
#define __RESOURCE_BASE_H__

#include "hash.h"

class CResourceBase {
public:
	void RefCountUp()const;
	void RefCountDown()const;
	bool RefCountZero()const;

	void SetHash(const hash _hash);
	hash GetHash()const;
	virtual void Finalize(){}
protected:
	hash m_hash = 0;
	mutable int m_resourceCounter = 0;
};

#endif // !__RESOURCE_BASE_H__
