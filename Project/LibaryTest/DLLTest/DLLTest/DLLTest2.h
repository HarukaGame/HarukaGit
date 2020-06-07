#pragma once
#ifdef DLLTEST_EXPORTS

#define DLLTEST_API __declspec(dllexport)
#else

#define DLLTEST_API __declspec(dllimport)

#endif

namespace DLLTest {
	class HelloWorld;
	class NextHelloWorld {
	public:
		DLLTEST_API NextHelloWorld();
		static DLLTEST_API void NextHello();
		DLLTEST_API void NextWorld();
	private:
		HelloWorld* a;
	};
}