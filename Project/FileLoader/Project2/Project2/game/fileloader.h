#pragma once

typedef int GLsizei;
typedef unsigned int GLuint;
class CFileLoader {
public:
    static const char* GetText(const char* filename, const char* code);
   bool CreateSource(const char* path);
    const char* GetSource();
    void Release();
    GLsizei length = 0;
    int readShaderSource(GLuint shader, const char* file);

private:
    void* source = nullptr;

};