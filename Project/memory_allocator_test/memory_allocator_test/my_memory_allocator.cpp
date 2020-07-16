#include "my_memory_allocator.h"
#include "preminum_lib.h"
#include <stdlib.h>
#include <stdio.h>

CMemoryAllocator CMemoryAllocator::s_instance;

bool CMemoryAllocator::Initialize() {
	PRINT("CMemoryAllocator::Initialize START\n");

	if (sizeof(MemoryInfo) > m_allocInfo.m_memoryBlockSize) {
		return false;
	}

	//メモリの確保
	m_allocInfo.m_pTopMemoryPtr = malloc(m_allocInfo.m_memoryBlockSize);

	//フリーで使えるポインタを設定
	m_allocInfo.freeMemoryPtr = m_allocInfo.m_pTopMemoryPtr;

	//確保したメモリの終端を登録
	m_allocInfo.m_pEndPtr = (void*)((char*)m_allocInfo.m_pTopMemoryPtr + m_allocInfo.m_memoryBlockSize);

	m_pDummyMemoryInfo = new(m_allocInfo.m_pTopMemoryPtr)MemoryInfo();
	m_pDummyMemoryInfo->m_memorySize = 0;

	s_instance = *this;

	PRINT("CMemoryAllocator::Initialize reserve [%d]byte\n",sizeof(MemoryInfo));
	return true;

}

void CMemoryAllocator::Finalize()
{
	if (s_instance.m_allocInfo.useCount != 0) {
		PRINT("useCount is %d\n", s_instance.m_allocInfo.useCount);
	}
	PRINT("CMemoryAllocator::Finalize\n");
	free(s_instance.m_allocInfo.m_pTopMemoryPtr);
}

void* CMemoryAllocator::MemoryMalloc(const unsigned int _size)
{
	//MemoryInfoのサイズを計算
	unsigned int infoSize = sizeof(MemoryInfo);

	MemoryInfo* preMemoryInfo = nullptr;
	void* freePoiter = s_instance.SearchMemoryBlockPtr(_size,preMemoryInfo);

	//終端のポインタがあらかじめ確保したメモリの中にあるか調べる
	if (freePoiter == nullptr) {
		return nullptr;
	}

	s_instance.m_allocInfo.useCount++;
	PRINT("Malloc [%d]byte + info[%d]byte = [%d]byte\n",_size,infoSize,_size + infoSize);

	return freePoiter;
}

void CMemoryAllocator::MemoryFree(void* _ptr)
{
	if (_ptr == nullptr) {
		return;
	}
	MemoryInfo* memInfo = (MemoryInfo*)((char*)_ptr - sizeof(MemoryInfo));
	if (memInfo == s_instance.m_pDummyMemoryInfo) {
		return;
	}
	s_instance.m_allocInfo.useCount--;
	memInfo->m_pNextMemoryInfo->m_pPreMemoryInfo = memInfo->m_pPreMemoryInfo;
	memInfo->m_pPreMemoryInfo->m_pNextMemoryInfo = memInfo->m_pNextMemoryInfo;
	memInfo = nullptr;
}

void* CMemoryAllocator::GetCurrentEndPointer() const
{
	MemoryInfo* tempMemoryInfo = m_pDummyMemoryInfo;
	while (tempMemoryInfo->m_pNextMemoryInfo != m_pDummyMemoryInfo) {
		tempMemoryInfo = tempMemoryInfo->m_pNextMemoryInfo;
	}
	return tempMemoryInfo->GetEndPointer();
}

void* CMemoryAllocator::GetReservedEndPointer() const
{
	return m_allocInfo.m_pEndPtr;
}

void* CMemoryAllocator::SearchMemoryBlockPtr(const unsigned int _size)
{
	void* endPointer = (void*)((char*)m_allocInfo.freeMemoryPtr + sizeof(MemoryInfo) + _size);
	//終端のポインタがあらかじめ確保したメモリの中にあるか調べる
	if (endPointer > m_allocInfo.m_pEndPtr) {
		return nullptr;
	}

	return m_allocInfo.freeMemoryPtr;
}

void* CMemoryAllocator::SearchMemoryBlockPtr(const unsigned int _size, MemoryInfo* _preMemoryInfo)
{
	MemoryInfo* tempMemoryInfo = m_pDummyMemoryInfo;
	unsigned int reservedSize = sizeof(MemoryInfo) + _size;
	//reservedSize += (4 - reservedSize % 4) % 4;
	void* endPointer = nullptr;
	while (tempMemoryInfo->m_pNextMemoryInfo != m_pDummyMemoryInfo) {
		MemoryInfo* nextMemoryInfo = tempMemoryInfo->m_pNextMemoryInfo;

		endPointer = (void*)((char*)tempMemoryInfo->GetEndPointer() + reservedSize);

		if (endPointer < nextMemoryInfo->GetStartPoiter()) {
			break;
		}
		tempMemoryInfo = tempMemoryInfo->m_pNextMemoryInfo;
	}

	endPointer = (void*)((char*)tempMemoryInfo->GetEndPointer() + reservedSize);
	if (endPointer > m_allocInfo.m_pEndPtr) {
		return nullptr;
	}

	MemoryInfo* newMemoryInfo = new(tempMemoryInfo->GetEndPointer())MemoryInfo();
	newMemoryInfo->m_memorySize = _size;

	newMemoryInfo->m_pNextMemoryInfo = tempMemoryInfo->m_pNextMemoryInfo;
	tempMemoryInfo->m_pNextMemoryInfo = newMemoryInfo;

	newMemoryInfo->m_pNextMemoryInfo->m_pPreMemoryInfo = newMemoryInfo;
	newMemoryInfo->m_pPreMemoryInfo = tempMemoryInfo;

	_preMemoryInfo = newMemoryInfo;
	return newMemoryInfo->GetMemory();

}
