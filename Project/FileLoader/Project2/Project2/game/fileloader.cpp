#include "fileloader.h"
#include <iostream>
#include <string>
#include <fstream>
#include "GL/glew.h"
#  pragma warning(disable: 4996)

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

bool CFileLoader::CreateSource(const char* path)
{
    FILE* fp;

    fp = fopen(path, "rb");
    if (fp == nullptr) {
        printf("fopen error\n");
        return false;
    }

    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);

    source = malloc(length);
    if (source == nullptr) {
        return false;
    }
    fseek(fp, 0L, SEEK_SET);

    bool success = fread(source, sizeof(char), length, fp) != (size_t)length;
    fclose(fp);

    if (success) {
        return false;
    }

    return true;
}

const char* CFileLoader::GetSource()
{
    return (const char*)source;
}

void CFileLoader::Release()
{
    free(source);
}
