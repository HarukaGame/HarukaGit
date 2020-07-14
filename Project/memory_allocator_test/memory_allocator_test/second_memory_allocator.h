#pragma once

#ifndef __SECOND_MEMORY_ALLOCATOR_H__
#define __SECOND_MEMORY_ALLOCATOR_H__

namespace PREMIUM {
#define MEMORY_SIZE (1024)
#define ALIGNMENT_8 (8)

	struct MemHeader {
		MemHeader* m_pPrev = nullptr;
		MemHeader* m_pNext = nullptr;
		unsigned int m_memorySize = 0;
		bool m_isUsed = false;
	};

	class MemBlock {
	private:
		MemHeader m_memHader;
	public:
		void* GetBlockBuffer();
		void* GetMemoryBuffer();
	};

	class MemoryAllocator {
	public:
		bool Initialize();
		void Finalize();
		void* Malloc(const unsigned int _size);
		void Free(void* _ptr);
		void ShowInfo();
	private:
		void* SearchUseableMemBlock(const unsigned int _size);
		bool CheckMemorySize(const void* _start, const void* _end, const unsigned int _size);
		bool CheckMemorySize(const void* _start, const void* _end, const unsigned int _size, const unsigned int _align, void*& _ret);
	private:
		void* m_topPtr = nullptr;
		void* m_endPtr = nullptr;
		unsigned int m_memorySize = 0;
		unsigned int m_useCount = 0;
		MemBlock* m_pStartMemBlock = nullptr;
	};
}

#include "second_memory_allocator.inl"

#endif // !__SECOND_MEMORY_ALLOCATOR_H__
