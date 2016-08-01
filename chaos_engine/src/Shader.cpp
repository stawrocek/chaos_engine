#include "Shader.hpp"

using namespace chaos;

Shader::Shader(std::string fpath, GLenum type){
    loadFromFile(fpath, type);
}

Shader::~Shader(){
    glDeleteShader(id);
    std::cout << "Destructor of shader " << getShaderName() << "\n";
}

void Shader::loadFromFile(std::string fpath, GLenum type){
    std::ifstream file(fpath);
    if(!file){
        std::cout << "[error]: couldn't open " << fpath << "\n";
    }
    shaderCode = std::string((std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>());
    compile(type);
}

void Shader::loadFromString(std::string str, GLenum type){
    shaderCode = str;
    compile(type);
}

bool Shader::compile(GLenum type){
    shaderType = type;
    id = glCreateShader(type);
    const GLchar* tmpCode = &shaderCode[0];
    glShaderSource(id, 1, &tmpCode, NULL);
    glCompileShader(id);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::"+getShaderName()+"::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return success;
}

GLuint Shader::getId(){
    return id;
}

std::string Shader::getShaderName(){
    if(shaderType == GL_VERTEX_SHADER)return "VERTEX_SHADER";
    if(shaderType == GL_FRAGMENT_SHADER)return "FRAGMENT_SHADER";
    if(shaderType == GL_GEOMETRY_SHADER) return "GEOMETRY_SHADER";
    return "[error] UNKNOWN_SHADER [error]";
}
