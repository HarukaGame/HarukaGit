#pragma once
#ifndef __MY_MEMORY_ALLOCATOR_H__
#define __MY_MEMORY_ALLOCATOR_H__

#define MEMORY_SIZE (200)

#include "debug_print.h"


struct AllocInfo {
	unsigned int m_memoryBlockSize = 0;
	void* m_pTopMemoryPtr = nullptr;
	void* m_pEndPtr = nullptr;
	void* freeMemoryPtr = nullptr;
	unsigned int useCount = 0;
	AllocInfo(const unsigned int _size) {
		m_memoryBlockSize = _size;
	}
};
struct MemoryInfo {
	MemoryInfo* m_pNextMemoryInfo = nullptr;
	MemoryInfo* m_pPreMemoryInfo = nullptr;
	unsigned int m_memorySize = 0;
	MemoryInfo() {
		m_pNextMemoryInfo = this;
		m_pPreMemoryInfo = this;
	}

	char* GetMemory() {
		return (char*)this + sizeof(MemoryInfo);
	}
	void* GetStartPoiter()const {
		return (void*)this;
	}
	void* GetEndPointer()const {
		return (void*)((char*)this + sizeof(MemoryInfo) + m_memorySize);
	}
};

class CMemoryAllocator {
public:
	bool Initialize();
	void Finalize();
	void* MemoryMalloc(const unsigned int _size);
	void MemoryFree(void* _ptr);

	template<class T>T* MemoryNew();

	void* GetCurrentEndPointer()const;
	void* GetReservedEndPointer()const;
private:
	static CMemoryAllocator s_instance;
	void* SearchMemoryBlockPtr(const unsigned int _size);
	void* SearchMemoryBlockPtr(const unsigned int _size, MemoryInfo* _preMemoryInfo);
	AllocInfo m_allocInfo = AllocInfo(MEMORY_SIZE);
	void* m_pMemoryPointer = nullptr;
	MemoryInfo* m_pDummyMemoryInfo = nullptr;
};

template<class T>
T* CMemoryAllocator::MemoryNew()
{
	unsigned int size = sizeof(T);
	void* reservedPtr = MemoryMalloc(size);
	if (reservedPtr == nullptr) {
		return nullptr;
	}


	//m_allocInfo.freeMemoryPtr = (void*)((char*)m_allocInfo.freeMemoryPtr + sizeof(MemoryInfo));

	T* retPtr = new(reservedPtr)T();
	//m_allocInfo.freeMemoryPtr = (void*)((char*)m_allocInfo.freeMemoryPtr + memInfo->m_memorySize);

	return retPtr;
}

#endif // !__MY_MEMORY_ALLOCATOR_H__

