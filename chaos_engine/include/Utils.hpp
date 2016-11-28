#ifndef UTILS_HPP
#define UTILS_HPP

#include "Export.hpp"

#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

namespace chaos{

template <typename T>
std::string CHAOS_EXPORT toString ( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

long CHAOS_EXPORT getFileSize(FILE* f)
{
    long size = 0;
    fseek(f, 0L, SEEK_END), size = ftell(f), fseek(f, 0L, SEEK_SET);
    return size;
};

std::string CHAOS_EXPORT getFileAsString(const std::string& path)
{
    FILE* f = fopen(path.c_str(), "rb");
    long sizeBytes = 0;

    if(!f)
    {
        printf("Failed to open file %s\n", path.c_str());
        exit(0);
    }
    sizeBytes = getFileSize(f);

    std::vector<GLchar> code;
    code.resize(sizeBytes + 1);

    if(fread(&code[0], sizeBytes, 1, f) != 1)
    {
        printf("Unable to read %s\n", path.c_str());
        exit(0);
    }

    code[sizeBytes] = 0;
    return std::string(code.begin(), code.end());
}

}
#endif // UTILS_HPP
