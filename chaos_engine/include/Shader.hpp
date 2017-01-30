#ifndef SHADER_HPP
#define SHADER_HPP

#include "Export.hpp"

#include <string>
#include <iostream>
#include <streambuf>
#include <fstream>

namespace chaos{

class CHAOS_EXPORT Shader
{
public:
    Shader();
    Shader(std::string fpath, GLenum type);
    virtual ~Shader();
    void loadFromFile(std::string fpath, GLenum type);
    void loadFromString(std::string str, GLenum type);
    bool compile(GLenum type);
    GLuint getId();
    std::string getShaderName();

private:
    std::string shaderCode;
    GLuint id;
    GLenum shaderType;
};

}
#endif // SHADER_HPP
