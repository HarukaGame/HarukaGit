#include "debug_print.h"
#include "second_memory_allocator.h"

namespace PREMIUM {
	void* MemBlock::GetBlockBuffer() {
		return (void*)this;
	}
	void* MemBlock::GetMemoryBuffer() {
		return (void*)((unsigned char*)this + sizeof(MemBlock));
	}


	bool MemoryAllocator::Initialize() {
		m_topPtr = malloc(MEMORY_SIZE);
		if (m_topPtr == nullptr) {
			return false;
		}

		m_memorySize = MEMORY_SIZE;

		//1byteで取得するためunsigned char*でキャスト
		m_endPtr = (void*)((unsigned char*)m_topPtr + m_memorySize);
		return true;
	}
	void MemoryAllocator::Finalize(){
		if (m_useCount != 0) {
			PRINT("m_useCount is not 0\n");
		}
		free(m_topPtr);
	}
	void* MemoryAllocator::Malloc(const unsigned int _size){
		void* ret = SearchUseableMemBlock(_size);
		if (ret == nullptr) {
			PRINT("MemoryAllocator::Malloc do not exist enough\n");
			return nullptr;
		}
		m_useCount++;
		return ret;
	}
	void MemoryAllocator::Free(void* _ptr){
	}
	void MemoryAllocator::ShowInfo() {
		PRINT("top pointer:%p\n", m_topPtr);
		PRINT("end pointer:%p\n", m_endPtr);
	}
	void* MemoryAllocator::SearchUseableMemBlock(const unsigned int _size) {
		unsigned int blockSize = _size + sizeof(MemBlock);
		if (m_pStartMemBlock == nullptr) {
			void* tempPtr = nullptr;
			if (CheckMemorySize(m_topPtr, m_endPtr, blockSize,16,tempPtr)) {
				m_pStartMemBlock = new(tempPtr)MemBlock();
				return m_pStartMemBlock->GetMemoryBuffer();
			}
			else {
				return nullptr;
			}
		}
		
		return nullptr;
	}

	bool MemoryAllocator::CheckMemorySize(const void* _start, const void* _end, const unsigned int _size) {
		return (unsigned char*)m_endPtr - (unsigned char*)m_topPtr >= _size;
	}
	bool MemoryAllocator::CheckMemorySize(const void* _start, const void* _end, const unsigned int _size, const unsigned int _align,void*& _ret)
	{
		unsigned long padding = (_align - (unsigned long)_start % _align)%_align;
		_ret = (void*)((unsigned char*)_start + padding);
		return (unsigned char*)m_endPtr - (unsigned char*)_ret >= _size;
	}
}