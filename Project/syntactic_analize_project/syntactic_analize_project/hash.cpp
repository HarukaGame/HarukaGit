#include "hash.h"

unsigned long CHash::CRC32(const char* _str)
{
    unsigned const char* buff = (unsigned const char*)_str;
    return CHash::GetMemCRC32(0xFFFFFFFF, buff, strlen(_str)) ^ 0xFFFFFFFF;
}

unsigned long CHash::CRC32(const char* _data, size_t _size)
{
    unsigned const char* buff = (unsigned const char*)_data;
    return CHash::GetMemCRC32(0xFFFFFFFF, buff, _size);
}

unsigned long CHash::GetMemCRC32(unsigned long crc32, unsigned const char* buff, size_t size){
    while (size != 0) {
        crc32 = CRC32Table[(crc32 >> (32 - CHAR_BIT)) ^ *buff] ^ (crc32 << CHAR_BIT);
        buff++;
        size--;
    }
    return crc32;
}