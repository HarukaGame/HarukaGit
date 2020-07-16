#pragma once

#ifndef __SECOND_MEMORY_ALLOCATOR_H__
#define __SECOND_MEMORY_ALLOCATOR_H__

namespace PREMIUM {
#define MEMORY_SIZE (1024)
#define ALIGNMENT_8 (8)

	class MemHeader {
	private:
		MemHeader* m_pPrev = nullptr;
		MemHeader* m_pNext = nullptr;
		unsigned int m_memorySize = 0;
		bool m_isUsed = false;
	public:
		void* GetStartBuffer()const;
		void* GetMemoryBuffer()const;
		void* GetEndPtr()const;
		void SetMemorySize(const unsigned int _size) { m_memorySize = _size; };
		unsigned int GetMemorySize()const { return m_memorySize; };
		MemHeader* Next()const { return m_pNext; };
		void Insert(MemHeader* _header);
	};

	class MemoryAllocator {
	public:
		bool Initialize();
		void Finalize();
		void* Malloc(const unsigned int _size, const unsigned int _align);
		void Free(void* _ptr);
		void ShowInfo();
	private:
		void* SearchAlignmentPtr(void* start,void* end, unsigned int _align);
		void* SearchUseableMemBlock(const unsigned int _size, const unsigned int _align);
		bool CheckMemorySize(const void* _start, const void* _end, const unsigned int _size);
		bool CheckMemorySize(void* _start,void* _end, const unsigned int _size, const unsigned int _align, void*& _ret);
	private:
		void* m_topPtr = nullptr;
		void* m_endPtr = nullptr;
		unsigned int m_memorySize = 0;
		unsigned int m_useCount = 0;
		MemHeader* m_pStartMemHeader = nullptr;
	};
}

#include "second_memory_allocator.inl"

#endif // !__SECOND_MEMORY_ALLOCATOR_H__
