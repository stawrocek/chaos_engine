#include "../include/Skybox.hpp"

chaos::Skybox::Skybox(Renderer* ren, CubeMap* cb)
:GameObject(ren,"CubeMap:Vao_Pos", "Shader_Skybox")
{
    setCubeMap(cb);
}

chaos::Skybox::~Skybox(){}

void chaos::Skybox::draw(){
    glDepthMask(GL_FALSE);
    shader->run();
    cubeMap->bind();
    glActiveTexture(GL_TEXTURE0);
    shader->setUniform("mx",renderer->getActiveCamera()->getProjectionMatrix() * glm::mat4(glm::mat3(renderer->getActiveCamera()->getViewMatrix()))*getGlobalTransformMatrix());
    vao->bind();
    vao->draw(shader);
    vao->unbind();
    glDepthMask(GL_TRUE);
}

void chaos::Skybox::setCubeMap(chaos::CubeMap* cb){
    cubeMap = cb;
}
chaos::CubeMap* chaos::Skybox::getCubeMap(){
    return cubeMap;
}
