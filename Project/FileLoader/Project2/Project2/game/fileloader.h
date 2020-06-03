#pragma once

typedef int GLsizei;
class CFileLoader {
public:
    static const char* GetText(const char* filename, const char* code);
   bool CreateSource(const char* path);
    const char* GetSource();
    void Release();
    GLsizei length = 0;

private:
    void* source = nullptr;

};