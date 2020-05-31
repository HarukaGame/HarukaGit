#include "fileloader.h"
#include <iostream>
#include <string>
#include <fstream>

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