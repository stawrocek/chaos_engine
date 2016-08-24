#ifndef RENDERER_HPP
#define RENDERER_HPP

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

        addShader({std::make_pair("files/shaders/font0.vs", GL_VERTEX_SHADER),
                                       std::make_pair("files/shaders/font0.fs", GL_FRAGMENT_SHADER)}, "Shader_Font2d");

        std::vector<GLfloat> rect_Pos = {
            -1.f, -1.f, 0.f,
             1.f, -1.f, 0.f,
            -1.f,  1.f, 0.f,
             1.f,  1.f, 0.f,
             1.f, -1.f, 0.f,
            -1.f,  1.f, 0.f
        };

        std::vector<GLfloat> rect_Pos_Uv = {
            -1.f, -1.f, 0.f,    0.f, 0.f,
             1.f, -1.f, 0.f,    1.f, 0.f,
            -1.f,  1.f, 0.f,    0.f, 1.f,
             1.f,  1.f, 0.f,    1.f, 1.f,
             1.f, -1.f, 0.f,    1.f, 0.f,
            -1.f,  1.f, 0.f,    0.f, 1.f
        };

        std::vector<GLfloat> cube_Pos = {
            -1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f,  1.f, -1.f,
             1.f,  1.f, -1.f,
            -1.f,  1.f, -1.f,
            -1.f, -1.f, -1.f,

            -1.f, -1.f,  1.f,
             1.f, -1.f,  1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
            -1.f,  1.f,  1.f,
            -1.f, -1.f,  1.f,

            -1.f,  1.f,  1.f,
            -1.f,  1.f, -1.f,
            -1.f, -1.f, -1.f,
            -1.f, -1.f, -1.f,
            -1.f, -1.f,  1.f,
            -1.f,  1.f,  1.f,

             1.f,  1.f,  1.f,
             1.f,  1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f,  1.f,
             1.f,  1.f,  1.f,

            -1.f, -1.f, -1.f,
             1.f, -1.f, -1.f,
             1.f, -1.f,  1.f,
             1.f, -1.f,  1.f,
            -1.f, -1.f,  1.f,
            -1.f, -1.f, -1.f,

            -1.f,  1.f, -1.f,
             1.f,  1.f, -1.f,
             1.f,  1.f,  1.f,
             1.f,  1.f,  1.f,
            -1.f,  1.f,  1.f,
            -1.f,  1.f, -1.f
        };

        std::vector<GLfloat> cube_Pos_Uv = {
            -1.f, -1.f, -1.f,  0.0f, 0.0f,
             1.f, -1.f, -1.f,  1.0f, 0.0f,
             1.f,  1.f, -1.f,  1.0f, 1.0f,
             1.f,  1.f, -1.f,  1.0f, 1.0f,
            -1.f,  1.f, -1.f,  0.0f, 1.0f,
            -1.f, -1.f, -1.f,  0.0f, 0.0f,

            -1.f, -1.f,  1.f,  0.0f, 0.0f,
             1.f, -1.f,  1.f,  1.0f, 0.0f,
             1.f,  1.f,  1.f,  1.0f, 1.0f,
             1.f,  1.f,  1.f,  1.0f, 1.0f,
            -1.f,  1.f,  1.f,  0.0f, 1.0f,
            -1.f, -1.f,  1.f,  0.0f, 0.0f,

            -1.f,  1.f,  1.f,  1.0f, 0.0f,
            -1.f,  1.f, -1.f,  1.0f, 1.0f,
            -1.f, -1.f, -1.f,  0.0f, 1.0f,
            -1.f, -1.f, -1.f,  0.0f, 1.0f,
            -1.f, -1.f,  1.f,  0.0f, 0.0f,
            -1.f,  1.f,  1.f,  1.0f, 0.0f,

             1.f,  1.f,  1.f,  1.0f, 0.0f,
             1.f,  1.f, -1.f,  1.0f, 1.0f,
             1.f, -1.f, -1.f,  0.0f, 1.0f,
             1.f, -1.f, -1.f,  0.0f, 1.0f,
             1.f, -1.f,  1.f,  0.0f, 0.0f,
             1.f,  1.f,  1.f,  1.0f, 0.0f,

            -1.f, -1.f, -1.f,  0.0f, 1.0f,
             1.f, -1.f, -1.f,  1.0f, 1.0f,
             1.f, -1.f,  1.f,  1.0f, 0.0f,
             1.f, -1.f,  1.f,  1.0f, 0.0f,
            -1.f, -1.f,  1.f,  0.0f, 0.0f,
            -1.f, -1.f, -1.f,  0.0f, 1.0f,

            -1.f,  1.f, -1.f,  0.0f, 1.0f,
             1.f,  1.f, -1.f,  1.0f, 1.0f,
             1.f,  1.f,  1.f,  1.0f, 0.0f,
             1.f,  1.f,  1.f,  1.0f, 0.0f,
            -1.f,  1.f,  1.f,  0.0f, 0.0f,
            -1.f,  1.f, -1.f,  0.0f, 1.0f
        };

        GLuint circleCount = 32;
        GLfloat lastX = 1.f;
        GLfloat lastY = 0.f;
        std::vector<GLfloat> circle_Pos;
        for(GLuint i = 1; i <= circleCount; i++){
            circle_Pos.insert(circle_Pos.end(), {0.f, 0.f, 0.f});
            circle_Pos.insert(circle_Pos.end(), {lastX, lastY, 0.f});
            lastX = cos(i*(6.283f/(GLfloat)circleCount));
            lastY = sin(i*(6.283f/(GLfloat)circleCount));
            circle_Pos.insert(circle_Pos.end(), {lastX, lastY, 0.0f});
        }


        addVAO(3, 0, 0, 0, &rect_Pos, "Rectangle:Vao_Pos");
        addVAO(3, 0, 2, 0, &rect_Pos_Uv, "Rectangle:Vao_Pos.Uv");
        addVAO(3, 0, 0, 0, &cube_Pos, "Cube:Vao_Pos");
        addVAO(3, 0, 2, 0, &cube_Pos_Uv, "Cube:Vao_Pos.Uv");
        addVAO(3, 0, 0, 0, &circle_Pos, "Circle:Vao_Pos");
    }

    glm::mat4 getCamCombined(){
        return camCombined;
    }

    void setCamCombined(glm::mat4 mx){
        camCombined = mx;
    }

private:
    std::unordered_map<std::string , ShaderProgram*> cacheShaders;
    std::unordered_map<std::string , VertexArray*> cacheVAO;
    glm::mat4 camCombined = glm::mat4();
};

}

#endif //RENDERER_HPP


