#include "pch.h"
#include "DLLTest.h"
#include <iostream>

namespace DLLTest {
	HelloWorld::HelloWorld() {
		hoge = 32;
		std::cout << "HelloWorld" << hoge << std::endl;
	}

	void HelloWorld::hello() {
		std::cout << "Hello";
		return;
	}

	void HelloWorld::world() {
		std::cout << "world";
		return;

	}
}