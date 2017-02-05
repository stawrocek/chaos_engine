#ifndef SHADER_HPP
#define SHADER_HPP

#include "Export.hpp"
#include "Application.hpp"

#include <string>
#include <sstream>
#include <vector>
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
    static std::string translateGL3ShaderGLES2Shader(std::string shader, GLenum type);
    static std::string getToken(std::string str){
        std::string out;
        bool add=false;
        for(int i = 0; i < str.size(); i++){
            if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r'){
                add=true;
            }
            if(str[i] == ' ' && add)
                return out;
            if(add)
                out += str[i];
        }
        return out;
    }
private:
    std::string shaderCode;
    GLuint id;
    GLenum shaderType;
};

}
#endif // SHADER_HPP
