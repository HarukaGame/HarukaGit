#pragma once

#ifdef DLLTEST_EXPORTS

#define DLLTEST_API __declspec(dllexport)
#else

#define DLLTEST_API __declspec(dllimport)

#endif

namespace DLLTest{
	class HelloWorld {
	public:
		DLLTEST_API HelloWorld();
		static DLLTEST_API void hello();
		DLLTEST_API void world();
	private:
		int hoge = 0;
	};
}