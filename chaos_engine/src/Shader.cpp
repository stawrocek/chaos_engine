#include "../include/Shader.hpp"

#include <sstream>
#include <iostream>
#include <streambuf>
#include <fstream>

#include "../include/Logger.hpp"

chaos::Shader::Shader()
:id(-1)
{}

chaos::Shader::Shader(std::string fpath, GLenum type){
    loadFromFile(fpath, type);
}

chaos::Shader::~Shader(){
    glDeleteShader(id);
}

void chaos::Shader::loadFromFile(std::string fpath, GLenum type){
    fpath = chaos::Application::getDataStorageDirectory()+fpath;
    std::ifstream file(fpath);

    if(!file){
        SHOUT("[error]: couldn't open %s", fpath.c_str());
    }
    shaderCode = std::string((std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>());
    compile(type);
}

void chaos::Shader::loadFromString(std::string str, GLenum type){
    shaderCode = str;
    compile(type);
}

bool chaos::Shader::compile(GLenum type){
    #if defined(ANDROID) || defined(__EMSCRIPTEN__)
    shaderCode = translateGL3ShaderGLES2Shader(shaderCode, type);
    #endif // ANDROID || __EMSCRIPTEN__

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
        SHOUT("ERROR::SHADER::COMPILATION_FAILED: %s, (%s)", infoLog, getShaderName().c_str());
    }
    return success;
}

GLuint chaos::Shader::getId(){
    return id;
}

std::string chaos::Shader::getShaderName(){
    if(shaderType == GL_VERTEX_SHADER)return "VERTEX_SHADER";
    if(shaderType == GL_FRAGMENT_SHADER)return "FRAGMENT_SHADER";
    //opengl ES 3.2 and higher
    #ifdef GEOMETRY_SHADER_ENABLED
    if(shaderType == GL_GEOMETRY_SHADER) return "GEOMETRY_SHADER";
    #endif
    return "[error] UNKNOWN_SHADER [error]";
}

//temporary solution, need real parser
std::string chaos::Shader::translateGL3ShaderGLES2Shader(std::string shader, GLenum type){
    std::stringstream ss(shader);
    std::string line;
    std::string out;
    bool main=false;
    if (shader != "") {
        while(std::getline(ss,line,'\n')){
            if(main || (line.find("main(") != -1 || line.find("main (") != -1)){
                main=true;
            }

            if(line.find("#") != std::string::npos && line.find("version") != std::string::npos){
                out += "#version 100\n";
                if(type == GL_FRAGMENT_SHADER)
                    out += "precision mediump float;\n";
                else
                    out += "precision highp float;\n";
            }
            else if(line.find("layout") != std::string::npos && line.find("location") != std::string::npos){
                out += "attribute ";
                bool spaceEnd=false;
                for(size_t i = line.find("in")+2; i < line.size(); i++){
                    if(line[i] != ' '){
                        spaceEnd=true;
                    }
                    if(spaceEnd)
                        out += line[i];
                }
                out += "\n";
            }
            else if(type == GL_FRAGMENT_SHADER && line.find("out vec4 color;") != std::string::npos){
                //skip
            }
            else if(getToken(line) == "out"){
                out += "varying ";
                bool spaceEnd=false;
                for(size_t i = line.find("out")+3; i < line.size(); i++){
                    if(line[i] != ' '){
                        spaceEnd=true;
                    }
                    if(spaceEnd)
                        out += line[i];
                }
                out += "\n";
            }
            else if(getToken(line) == "in"){
                if(type == GL_FRAGMENT_SHADER)
                    out += "varying ";
                else if(type == GL_VERTEX_SHADER)
                    out += "attribute ";

                bool spaceEnd=false;
                for(size_t i = line.find("in")+2; i < line.size(); i++){
                    if(line[i] != ' '){
                        spaceEnd=true;
                    }
                    if(spaceEnd)
                        out += line[i];
                }
                out += "\n";
            }
            else if(type == GL_FRAGMENT_SHADER && line.find("texture") != std::string::npos && line.find("texture2d") == std::string::npos){
                std::string tmp = std::string(line.begin(), line.begin()+line.find("texture")) +
                                    "texture2D"
                                    + std::string(line.begin()+line.find("texture")+7, line.end());
                if(main && getToken(tmp) == "color"){
                    std::string tmp2 = std::string(tmp.begin(), tmp.begin()+tmp.find("color")) +
                                    "gl_FragColor"
                                    + std::string(tmp.begin()+tmp.find("color")+5, tmp.end());
                    out += tmp2+"\n";
                }
                else
                    out += tmp+"\n";
            }
            else if(main && getToken(line) == "color"){
                std::string tmp = std::string(line.begin(), line.begin()+line.find("color")) +
                                    "gl_FragColor"
                                    + std::string(line.begin()+line.find("color")+5, line.end());
                out += tmp+"\n";
            }
            else
                out += line+"\n";
        }
    }
    return out;
}

std::string chaos::Shader::getToken(std::string str){
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
