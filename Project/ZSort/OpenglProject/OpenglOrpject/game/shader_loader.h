#pragma once
#ifndef __SHADER_LOADER_H__
#define __SHADER_LOADER_H__

class CShaderLoader {
public:
	static int CreateShaderProgram(const char* _vertSource,int _vertLength, const char* _fragSource,int _fragLength);
};
#endif // !__SHADER_LOADER_H__
