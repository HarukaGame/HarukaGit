#pragma once

#ifndef __MEM_H__
#define __MEM_H__

struct Allocator {
	unsigned int fullSize = 0;
	void* freememPtr = nullptr;
};

struct MemInfo {
	unsigned int size;
	char mem[0];
};

#endif // !__MEM_H__
