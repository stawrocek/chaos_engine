#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <string>

#include "Transform.hpp"
#include "ShaderProgram.hpp"
#include "VertexArray.hpp"

#include <unordered_map>

namespace chaos{

class Renderer{
public:
    Renderer(){
        initEngineStuff();
    }
    virtual ~Renderer(){
        std::cout << "Destructor of Renderer{\n";
        std::cout << "cacheShaders.size() = " << cacheShaders.size() << "\n";
        auto itr = cacheShaders.begin();
        while (itr != cacheShaders.end()) {
            delete itr->second;
            itr = cacheShaders.erase(itr);
        }
        std::cout << "cacheShaders.size() = " << cacheShaders.size() << "\n";

        std::cout << "cacheVAO.size() = " << cacheVAO.size() << "\n";
        auto itr2 = cacheVAO.begin();
        while (itr2 != cacheVAO.end()) {
            delete itr2->second;
            itr2 = cacheVAO.erase(itr2);
        }
        std::cout << "cacheVAO.size() = " << cacheVAO.size() << "\n";

        std::cout << "}\n";
    }

    //Shaders

    ShaderProgram* addShader(const std::initializer_list<std::pair<std::string, GLenum>> &iniListShader, std::string id){
        if(cacheShaders.find(id) != cacheShaders.end()){
            return cacheShaders[id];
        }
        ShaderProgram* tmp = new ShaderProgram(iniListShader);
        cacheShaders[id] = tmp;
        return tmp;
    }

    ShaderProgram* getShader(std::string id){
        if(cacheShaders.find(id) == cacheShaders.end()){
            return nullptr;
        }
        return cacheShaders[id];
    }

    void removeShader(std::string id){
        if(cacheShaders.find(id) != cacheShaders.end()){
            delete cacheShaders[id];
            cacheShaders.erase(id);
        }
    }

    //VAO

    VertexArray* addVAO(GLuint vertsSize, GLuint colorSize, GLuint uvSize, GLuint dataSize, std::vector<GLfloat>* vec, std::string id){
        if(cacheVAO.find(id) != cacheVAO.end()){
            return cacheVAO[id];
        }
        VertexArray* tmp = new VertexArray(vertsSize, colorSize, uvSize, dataSize, vec);
        cacheVAO[id] = tmp;
        return tmp;
    }

    VertexArray* getVAO(std::string id){
        if(cacheVAO.find(id) == cacheVAO.end()){
            return nullptr;
        }
        return cacheVAO[id];
    }

    void removeVAO(std::string id){
        if(cacheVAO.find(id) != cacheVAO.end()){
            delete cacheVAO[id];
            cacheVAO.erase(id);
        }
    }

    void initEngineStuff(){
        // shaders will be as strings in final release
        addShader({std::make_pair("files/shaders/shader2.vs", GL_VERTEX_SHADER),
                                       std::make_pair("files/shaders/shader2.fs", GL_FRAGMENT_SHADER)}, "Shader_Pos");
        addShader({std::make_pair("files/shaders/shader1.vs", GL_VERTEX_SHADER),
                                       std::make_pair("files/shaders/shader1.fs", GL_FRAGMENT_SHADER)}, "Shader_Pos.Uv");

        std::vector<GLfloat> vx_Pos = {
            -1.f, -1.f, 0.f,
            1.f, -1.f, 0.f,
            -1.f,  1.f, 0.f,
            1.f, 1.f, 0.f,
            1.f, -1.f, 0.f,
            -1.f,  1.f, 0.f
        };

        std::vector<GLfloat> vx_Pos_Uv = {
            -1.f, -1.f, 0.f, 0.f, 0.f,
            1.f, -1.f, 0.f,  1.f, 0.f,
            -1.f,  1.f, 0.f, 0.f, 1.f,
            1.f, 1.f, 0.f,   1.f, 1.f,
            1.f, -1.f, 0.f,  1.f, 0.f,
            -1.f,  1.f, 0.f, 0.f, 1.f
        };

        addVAO(3, 0, 0, 0, &vx_Pos, "Vao_Pos");
        addVAO(3, 0, 2, 0, &vx_Pos_Uv, "Vao_Pos.Uv");
    }


private:
    std::unordered_map<std::string , ShaderProgram*> cacheShaders;
    std::unordered_map<std::string , VertexArray*> cacheVAO;

};

}

#endif //RENDERER_HPP


