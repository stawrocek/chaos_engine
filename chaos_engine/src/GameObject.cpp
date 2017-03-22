#include "../include/GameObject.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"
#include "../include/Renderer.hpp"

chaos::GameObject::GameObject(chaos::Renderer* ren)
:renderer(ren)
{}

chaos::GameObject::GameObject(chaos::Renderer* ren, std::string vaoId, std::string shaderId)
:renderer(ren)
{
    setVertexArray(vaoId);
    setShader(shaderId);
}

chaos::GameObject::~GameObject(){}

void chaos::GameObject::draw(){
    shader->run();
    if(!isLighting){
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
        shader->setUniform("uniColor", color);
    }
    else{
        shader->setUniform("model", getGlobalTransformMatrix());
        shader->setUniform("camCombined",renderer->getCamCombined());
        shader->setUniform("lightPos", glm::vec3(2.0, 0.0, 0.0));
        shader->setUniform("viewPos", glm::vec3(0.0, 0.0, 0.0));
        //shader->setUniform("viewPos", renderer->getActiveCamera()->getPosition());
        shader->setUniform("lightColor", glm::vec4(0.0, 1.0, 0.0, 1.0));
        shader->setUniform("objectColor", glm::vec4(0.2, 0.2, 0.7, 1.0));
    }

    vao->bind();
    vao->draw(shader);
    vao->unbind();
}

void chaos::GameObject::setVertexArray(std::string id){
    vao = renderer->getVAO(id);
}

chaos::VertexArray* chaos::GameObject::getVertexArray(){
    return vao;
}

void chaos::GameObject::setShader(std::string id){
shader = renderer->getShader(id);
}

chaos::ShaderProgram* chaos::GameObject::getShader(){
    return shader;
}

glm::vec4 chaos::GameObject::getColor(){
    return color;
}

void chaos::GameObject::setColor(glm::vec4 c){
    color = c;
}

void chaos::GameObject::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    color = glm::vec4(r, g, b, a);
}

chaos::Renderer* chaos::GameObject::getRenderer(){
    return renderer;
}

void chaos::GameObject::setRenderer(chaos::Renderer* ren){
    renderer = ren;
}

void chaos::GameObject::drawGizmo(GLfloat scale){
    renderer->drawDebugLine(getPosition(), getPosition()-scale*getFront(), glm::vec4(0,1,0,1));
    renderer->drawDebugLine(getPosition(), getPosition()+scale*getRight(), glm::vec4(1,0,0,1));
    renderer->drawDebugLine(getPosition(), getPosition()+scale*getUp(), glm::vec4(0,0,1,1));
}

void chaos::GameObject::setLightingEnabled(GLboolean enable){
    isLighting = enable;
}

GLboolean chaos::GameObject::isLightingEnabled(){
    return isLighting;
}



