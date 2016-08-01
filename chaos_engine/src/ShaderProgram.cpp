#include "ShaderProgram.hpp"

using namespace chaos;

ShaderProgram::ShaderProgram(const std::initializer_list<std::pair<std::string, GLenum>> &listShaders){
    id = glCreateProgram();
    std::vector<Shader*> vecShaders;
    for (auto shaderPair : listShaders) {
        vecShaders.push_back(new Shader(shaderPair.first, shaderPair.second));
        glAttachShader(id, vecShaders.back()->getId());
    }
    glLinkProgram(id);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //destructor of Shader will call glDeleteShader on every element of vecShader
    for (int i = 0; i < vecShaders.size(); i++) {
        delete vecShaders[i];
    }
}

ShaderProgram::~ShaderProgram(){
    std::cout << "Destructor of ShaderProgram\n";
    glDeleteProgram(id);
}

GLuint ShaderProgram::getId(){
    return id;
}

void ShaderProgram::run(){
    glUseProgram(id);
}
