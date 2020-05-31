#include "fileloader.h"
#include <iostream>
#include <string>
#include <fstream>

const char* CFileLoader::GetText(const char* filename, const char* code) {
    //ƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ
    std::ifstream ifs(filename);
    if (!ifs)
    {
        printf("%s‚ğ“Ç‚İ‚ß‚Ü‚¹‚ñ‚Å‚µ‚½\n", filename);
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