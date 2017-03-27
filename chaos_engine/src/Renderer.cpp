#include "../include/Renderer.hpp"

#include <iostream>

#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"
#include "../include/MeshPrefab.hpp"
#include "../include/Utils.hpp"
#include "../include/Window.hpp"


chaos::Renderer::Renderer(Window* w){
    setTargetWindow(w);
    initEngineStuff();
}

chaos::Renderer::~Renderer(){
    auto itr = cacheShaders.begin();
    while (itr != cacheShaders.end()) {
        delete itr->second;
        itr = cacheShaders.erase(itr);
    }

    auto itr2 = cacheVAO.begin();
    while (itr2 != cacheVAO.end()) {
        delete itr2->second;
        itr2 = cacheVAO.erase(itr2);
    }
}

//Shaders

chaos::ShaderProgram* chaos::Renderer::addShader(const std::initializer_list<std::pair<std::string, GLenum>> &iniListShader, std::string id){
    if(cacheShaders.find(id) != cacheShaders.end()){
        return cacheShaders[id];
    }
    chaos::ShaderProgram* tmp = new ShaderProgram(iniListShader);
    cacheShaders[id] = tmp;
    return tmp;
}

chaos::ShaderProgram* chaos::Renderer::getShader(std::string id){
    if(cacheShaders.find(id) == cacheShaders.end()){
        return nullptr;
    }
    return cacheShaders[id];
}

void chaos::Renderer::removeShader(std::string id){
    if(cacheShaders.find(id) != cacheShaders.end()){
        delete cacheShaders[id];
        cacheShaders.erase(id);
    }
}

//VAO

chaos::VertexArray* chaos::Renderer::addVAO(GLuint vertsSize, GLuint colorSize, GLuint uvSize, GLuint dataSize, std::vector<GLfloat>* vec, std::string id){
    if(cacheVAO.find(id) != cacheVAO.end()){
        return cacheVAO[id];
    }
    chaos::VertexArray* tmp = new VertexArray(vertsSize, colorSize, uvSize, dataSize, vec);
    cacheVAO[id] = tmp;
    return tmp;
}

chaos::VertexArray* chaos::Renderer::getVAO(std::string id){
    if(cacheVAO.find(id) == cacheVAO.end()){
        return nullptr;
    }
    return cacheVAO[id];
}

void chaos::Renderer::removeVAO(std::string id){
    if(cacheVAO.find(id) != cacheVAO.end()){
        delete cacheVAO[id];
        cacheVAO.erase(id);
    }
}

void chaos::Renderer::initEngineStuff(){
    // shaders will be as strings in final release
    // hehe, final release, good one
    addShader({ std::make_pair("files/shaders/shader2.vs", GL_VERTEX_SHADER),
                std::make_pair("files/shaders/shader2.fs", GL_FRAGMENT_SHADER)}, "Shader_Pos");
    addShader({ std::make_pair("files/shaders/shader_pos_norm.vs", GL_VERTEX_SHADER),
                std::make_pair("files/shaders/shader_pos_norm.fs", GL_FRAGMENT_SHADER)}, "Shader_Pos.Norm");
    addShader({ std::make_pair("files/shaders/shader1.vs", GL_VERTEX_SHADER),
                std::make_pair("files/shaders/shader1.fs", GL_FRAGMENT_SHADER)}, "Shader_Pos.Uv");
    addShader({ std::make_pair("files/shaders/font0.vs", GL_VERTEX_SHADER),
                std::make_pair("files/shaders/font0.fs", GL_FRAGMENT_SHADER)}, "Shader_Font2d");
    addShader({ std::make_pair("files/shaders/Model3d.vs", GL_VERTEX_SHADER),
                std::make_pair("files/shaders/Model3d.fs", GL_FRAGMENT_SHADER)}, "Shader_Mesh3d");
    addShader({ std::make_pair("files/shaders/Model3dLightsOn.vs", GL_VERTEX_SHADER),
                std::make_pair("files/shaders/Model3dLightsOn.fs", GL_FRAGMENT_SHADER)}, "Shader_Mesh3dLightsOn");

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

    std::vector<GLfloat> rect_Pos_Id {
        0.0f,  0.0f, 0.0f, 4.0f,
        1.0f,  0.0f, 0.0f, 3.0f,
        0.0f,  1.0f, 0.0f, 1.0f,
        0.0f,  1.0f, 0.0f, 1.0f,
        1.0f,  0.0f, 0.0f, 3.0f,
        1.0f,  1.0f, 0.0f, 2.0f
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

    std::vector<GLfloat> cube_Pos_Normal = {
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,

        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,

         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
         1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
         1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
         1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
        -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,

        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f
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
    addVAO(3, 0, 0, 1, &rect_Pos_Id,"Rectangle:Pos_Id");
    addVAO(3, 0, 0, 0, &cube_Pos, "Cube:Vao_Pos");
    addVAO(3, 3, 0, 0, &cube_Pos_Normal, "Cube:Vao_Pos.Norm");
    addVAO(3, 0, 2, 0, &cube_Pos_Uv, "Cube:Vao_Pos.Uv");
    addVAO(3, 0, 0, 0, &circle_Pos, "Circle:Vao_Pos");
}

void chaos::Renderer::addMeshVAO(MeshPrefab* mesh){
    addVAO(3, 3, 2, 0, mesh->getVBOData(), "Mesh:Vao_Pos.Uv("+toString(mesh->getMeshId())+")");
}

glm::mat4 chaos::Renderer::getCamCombined(){
    return camCombined;
}

void chaos::Renderer::setCamCombined(glm::mat4 mx){
    camCombined = mx;
}

void chaos::Renderer::setTargetWindow(Window* _win){
    win = _win;
}

chaos::Window* chaos::Renderer::getTargetWindow(){
    return win;
}

//slow af
void chaos::Renderer::drawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec4 color){
    std::vector<GLfloat> vTmp = {start.x,start.y,start.z,end.x,end.y,end.z};
    VertexArray vaoTmp(3,0,0,0,&vTmp);
    getShader("Shader_Pos")->run();
    getShader("Shader_Pos")->setUniform("uniColor", color);
    getShader("Shader_Pos")->setUniform("mx", getCamCombined());
    vaoTmp.bind();
    vaoTmp.draw(getShader("Shader_Pos"),GL_LINES);
    vaoTmp.unbind();
}

chaos::Camera* chaos::Renderer::getActiveCamera(){
    return activeCamera;
}

void chaos::Renderer::setActiveCamera(chaos::Camera* cam){
    activeCamera = cam;
}

void chaos::Renderer::setLightCastersVector(std::vector<LightCaster*>* vec){
    vecLightCasters=vec;
}

std::vector<chaos::LightCaster*>* chaos::Renderer::getLightCastersVector(){
    return vecLightCasters;
}
