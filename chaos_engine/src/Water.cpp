#include "../include/Water.hpp"
#include "../include/Camera.hpp"
#include "../include/FBO.hpp"
#include "../include/Window.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"

chaos::Water::Water(chaos::Renderer* ren, Camera* cam)
:GameObject(ren, "Rectangle:Vao_Pos.Uv", "Shader_Water"), camera(cam)
{
    moveY(-1); //beceause vao is moved to -1
    setColor(0.0, 0.2, 0.6, 1.0);
    refractionFBO = new chaos::FBO(ren->getTargetWindow()->getWidth(), ren->getTargetWindow()->getHeight(), 1);
    reflectionFBO = new chaos::FBO(ren->getTargetWindow()->getWidth(), ren->getTargetWindow()->getHeight(), 1);
}

void chaos::Water::draw(){
    shader->run();
    reflectionFBO->getTexture(0)->bindOnSlot(0);
    refractionFBO->getTexture(0)->bindOnSlot(1);
    shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
    shader->setUniform("uniColor", color);
    vao->bind();
    vao->draw(shader);
    vao->unbind();
}

chaos::FBO* chaos::Water::getReflectionFBO(){
    return reflectionFBO;
}

chaos::FBO* chaos::Water::getRefractionFBO(){
    return refractionFBO;
}

chaos::Water::~Water(){
    delete reflectionFBO;
    delete refractionFBO;
}
