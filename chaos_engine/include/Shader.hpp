#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>

#include "Export.hpp"
#include "Application.hpp"

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
    static std::string translateGL3ShaderGLES2Shader(std::string shader, GLenum type);
    static std::string getToken(std::string str);
private:
    std::string shaderCode;
    GLuint id;
    GLenum shaderType;
};

}
#endif // SHADER_HPP
