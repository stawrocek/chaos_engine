#ifndef SHADER_HPP
#define SHADER_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <streambuf>
#include <fstream>

namespace chaos{

class Shader
{
public:
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
