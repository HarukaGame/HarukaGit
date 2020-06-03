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

    bool success = fread(source, 1, length, fp) != (size_t)length;
    fclose(fp);

    if (success) {
        return false;
    }

    return true;
}

const char* CFileLoader::GetSource()
{
    return (char*)source;
}

void CFileLoader::Release()
{
    free(source);
}

int CFileLoader::readShaderSource(GLuint shader, const char* file)
{
    FILE* fp;
    const GLchar* source;
    GLsizei length;
    int ret;

    /* ファイルを開く */
    fp = fopen(file, "rb");
    if (fp == NULL) {
        perror(file);
        return -1;
    }

    /* ファイルの末尾に移動し現在位置 (つまりファイルサイズ) を得る */
    fseek(fp, 0L, SEEK_END);
    length = ftell(fp);

    /* ファイルサイズのメモリを確保 */
    source = (GLchar*)malloc(length);
    if (source == NULL) {
        fprintf(stderr, "Could not allocate read buffer.\n");
        return -1;
    }

    /* ファイルを先頭から読み込む */
    fseek(fp, 0L, SEEK_SET);
    ret = fread((void*)source, 1, length, fp) != (size_t)length;
    fclose(fp);

    /* シェーダのソースプログラムのシェーダオブジェクトへの読み込み */
    if (ret)
        fprintf(stderr, "Could not read file: %s.\n", file);
    else
        glShaderSource(shader, 1, &source, &length);

    /* 確保したメモリの開放 */
    free((void*)source);

    return ret;
}
