#include "resource_base.h"
#include "debug_print.h"

void CResourceBase::RefCountUp()const {
	m_resourceCounter++;
	PRINT3("hash:%x refCounter is [%d]\n", m_hash, m_resourceCounter);
}

void CResourceBase::RefCountDown()const {
	m_resourceCounter--;
	PRINT3("hash:%x refCounter is [%d]\n", m_hash, m_resourceCounter);
}

bool CResourceBase::RefCountZero()const {
	return m_resourceCounter == 0;
}

void CResourceBase::SetHash(const hash _hash)
{
	m_hash = _hash;
}

hash CResourceBase::GetHash() const
{
	return m_hash;
}
