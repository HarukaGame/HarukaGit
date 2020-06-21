#pragma once


class CFileLoader {
public:
    bool LoadFile(const char* _filePath);
    const char* GetBuffer();
    int GetLength();
    void Release();
    static const char* GetText(const char* filename, const char* code);
private:
    void* m_pBuffer = nullptr;
    int m_length = 0;
};