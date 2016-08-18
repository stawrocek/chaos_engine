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

private:
    std::unordered_map<std::string , ShaderProgram*> cacheShaders;
    std::unordered_map<std::string , VertexArray*> cacheVAO;

};

}

#endif //RENDERER_HPP_HPP


