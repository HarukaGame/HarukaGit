#include "second_memory_allocator.h"
#include "debug_print.h"

namespace PREMIUM {
	void* MemHeader::GetStartBuffer()const {
		return static_cast<void*>(const_cast<MemHeader*>(this));
	}
	void* MemHeader::GetMemoryBuffer()const {
		return static_cast<void*>(static_cast<unsigned char*>(GetStartBuffer()) + sizeof(MemHeader));
	}
	void* MemHeader::GetEndPtr()const {
		return static_cast<void*>(static_cast<unsigned char*>(GetMemoryBuffer()) + m_memorySize);
	}

	inline void MemHeader::Insert(MemHeader* _header)
	{
		if (m_pNext != nullptr) {
			m_pNext->m_pPrev = _header;
			_header = m_pNext = m_pNext;
		}
		m_pNext = _header;
		_header->m_pPrev = this;
	}

	bool MemoryAllocator::Initialize() {
		m_topPtr = malloc(MEMORY_SIZE);
		if (m_topPtr == nullptr) {
			return false;
		}

		m_memorySize = MEMORY_SIZE;
		//1byteで取得するためunsigned char*でキャスト
		m_endPtr = static_cast<void*>(static_cast<unsigned char*>(m_topPtr) + m_memorySize);

		void* dummyHeaderPtr = SearchAlignmentPtr(m_topPtr, m_endPtr, 8);
		m_pStartMemHeader = new(dummyHeaderPtr)MemHeader();
		m_pStartMemHeader->SetMemorySize(0);

		return true;
	}
	void MemoryAllocator::Finalize(){
		if (m_useCount != 0) {
			PRINT("m_useCount is not 0\n");
		}
		free(m_topPtr);
	}
	void* MemoryAllocator::Malloc(const unsigned int _size,const unsigned int _align){
		void* ret = SearchUseableMemBlock(_size, _align);
		if (ret == nullptr) {
			PRINT("MemoryAllocator::Malloc do not exist enough\n");
			return nullptr;
		}
		PRINT("MALLOC align %d size %x byte\n", _align, _size);
		m_useCount++;
		return ret;
	}
	void MemoryAllocator::Free(void* _ptr){
	}
	void MemoryAllocator::ShowInfo() {
		PRINT("top pointer:%p\n", m_topPtr);
		PRINT("end pointer:%p\n", m_endPtr);
		MemHeader* memHeader = m_pStartMemHeader;
		PRINT("startMemHeader start %p\n", memHeader->GetStartBuffer());
		PRINT("startMemHeader end   %p\n", memHeader->GetEndPtr());
		unsigned int counter = 1;
		while (memHeader->Next() != nullptr) {
			memHeader = memHeader->Next();
			PRINT("MemHeader[%d} start %p\n", counter, memHeader->GetStartBuffer());
			PRINT("MemHeader[%d} end   %p\n", counter,memHeader->GetEndPtr());
			counter++;
		}

	}
	void* MemoryAllocator::SearchAlignmentPtr(void* start, void* end, unsigned int _align)
	{
		unsigned long long padding = (_align - reinterpret_cast<unsigned long long>(start)%_align)%_align;
		unsigned long long address = reinterpret_cast<unsigned long long>(start) + padding;
		if (address < reinterpret_cast<unsigned long long>(end)) {
			return reinterpret_cast<void*>(address);
		}
		return nullptr;
	}
	void* MemoryAllocator::SearchUseableMemBlock(const unsigned int _size,const unsigned int _align) {
		unsigned int blockSize = _size + sizeof(MemHeader);

		MemHeader* memHeader = m_pStartMemHeader;
		bool success = false;
		void* ret = nullptr;
		void* start = nullptr;
		void* end = nullptr;
		while (success == false && memHeader->Next() != nullptr) {
			start = memHeader->GetEndPtr();
			end = memHeader->GetStartBuffer();
			if (CheckMemorySize(start, end, blockSize, _align, ret) == false) {
				memHeader = memHeader->Next();
				continue;
			}
			success = true;
		}
		if (success == false) {
			start = memHeader->GetEndPtr();
			end = m_endPtr;
			if (CheckMemorySize(start, end, blockSize, _align, ret) == false) {
				return nullptr;
			}
			success = true;
		}
		if (success == false) {
			return nullptr;
		}

		MemHeader* newMemHeader = new(ret)MemHeader();
		if (newMemHeader == nullptr) {
			return nullptr;
		}
		memHeader->Insert(newMemHeader);
		newMemHeader->SetMemorySize(_size);
		return  newMemHeader->GetMemoryBuffer();
	}

	bool MemoryAllocator::CheckMemorySize(const void* _start, const void* _end, const unsigned int _size) {
		return (unsigned char*)m_endPtr - (unsigned char*)m_topPtr >= _size;
	}
	bool MemoryAllocator::CheckMemorySize(void* _start,void* _end, const unsigned int _size, const unsigned int _align,void*& _ret)
	{
		//unsigned long long padding = (_align - (unsigned long long)_start % _align)%_align;
		//_ret = (void*)((unsigned char*)_start + padding);
		_ret = SearchAlignmentPtr(_start, _end, _align);
		if (_ret == nullptr) {
			return false;
		}
		return (unsigned char*)m_endPtr - (unsigned char*)_ret >= _size;
	}
}