#include "../include/GameObject.hpp"

#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"
#include "../include/Renderer.hpp"
#include "../include/Camera.hpp"
#include "../include/LightCaster.hpp"
#include "../include/Utils.hpp"

#include <iostream>

chaos::GameObject::GameObject(chaos::Renderer* ren)
:renderer(ren), material(glm::vec4(1, 0.1, 0.4, 1.0), glm::vec4(0,1,0,1), 32)
{}

chaos::GameObject::GameObject(chaos::Renderer* ren, std::string vaoId, std::string shaderId)
:renderer(ren), material(glm::vec4(1, 0.1, 0.4, 1.0), glm::vec4(0,1,0,1), 32)
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
        shader->setUniform("uniViewPos", renderer->getActiveCamera()->getPosition());

        shader->setUniform("ambientStrength", 0.0f);
        shader->setUniform("ambientColor", glm::vec4(0, 1, 0, 1));

        shader->setUniform("uniMaterial.diffuseColor", material.getDiffuseColor());
        shader->setUniform("uniMaterial.specularColor", material.getSpecularColor());
        shader->setUniform("uniMaterial.shininess", material.getShininess());
        shader->setUniform("uniObjectColor", getColor());


        GLuint pointLightCtr=0, dirLightCtr=0, spotlightCtr=0;
        for(GLuint i = 0; i < renderer->getLightCastersVector()->size(); i++){
            if(renderer->getLightCastersVector()->at(i)->getLightType() == LightCaster::PointLight){
                renderer->getLightCastersVector()->at(i)->setupUniforms(shader, this, pointLightCtr);
                pointLightCtr++;
            }
            if(renderer->getLightCastersVector()->at(i)->getLightType() == LightCaster::DirectionalLight){
                renderer->getLightCastersVector()->at(i)->setupUniforms(shader, this, dirLightCtr);
                dirLightCtr++;
            }
            if(renderer->getLightCastersVector()->at(i)->getLightType() == LightCaster::Spotlight){
                renderer->getLightCastersVector()->at(i)->setupUniforms(shader, this, spotlightCtr);
                spotlightCtr++;
            }
        }

        shader->setUniform("uniPointLightsCount", pointLightCtr);
        shader->setUniform("uniDirLightsCount", dirLightCtr);
        shader->setUniform("uniSpotlightsCount", spotlightCtr);
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
