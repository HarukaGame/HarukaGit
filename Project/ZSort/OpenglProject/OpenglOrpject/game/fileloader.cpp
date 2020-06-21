#include "fileloader.h"
#include <iostream>
#include <string>
#include <fstream>
#  pragma warning(disable: 4996)
bool CFileLoader::LoadFile(const char* _filePath)
{
    FILE* fp;

    fp = fopen(_filePath, "rb");
    if (fp == nullptr) {
        printf("fopen error\n");
        return false;
    }

    fseek(fp, 0L, SEEK_END);
    m_length = ftell(fp);

    m_pBuffer = malloc(m_length);
    if (m_pBuffer == nullptr) {
        return false;
    }
    fseek(fp, 0L, SEEK_SET);

    bool success = fread(m_pBuffer, 1, m_length, fp) != (size_t)m_length;
    fclose(fp);

    if (success) {
        return false;
    }

    return true;

}

const char* CFileLoader::GetBuffer()
{
    return (const char*)m_pBuffer;
}

int CFileLoader::GetLength()
{
    return m_length;
}

void CFileLoader::Release()
{
    free(m_pBuffer);
}

const char* CFileLoader::GetText(const char* filename, const char* code) {
    //ファイルの読み込み
    std::ifstream ifs(filename);
    if (!ifs)
    {
        printf("%sを読み込めませんでした\n", filename);
        return "";
    }

    std::string source;
    std::string line;
    while (getline(ifs, line))
    {
        source += line + "\n";
    }

    code = source.c_str();
    std::cout << code << std::endl;
    return code;

}