#include "pch.h"
#include "DLLTest2.h"
#include "DLLTest.h"
#include <iostream>

namespace DLLTest {
	NextHelloWorld::NextHelloWorld()
	{
		std::cout << "NextHelloWorld\n";
		a = new HelloWorld();
	}
	void NextHelloWorld::NextHello() {
		std::cout << "Next";
		 HelloWorld::hello();
	}
	void NextHelloWorld::NextWorld()
	{
		std::cout << "Next";

		a->world();
	}
}