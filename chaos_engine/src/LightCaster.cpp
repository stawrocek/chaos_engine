#include "../include/LightCaster.hpp"

#include "../include/Scene.hpp"
#include "../include/Utils.hpp"

chaos::LightCaster::LightCaster(chaos::Renderer * ren, chaos::Scene* scn, LightType lt)
:GameObject(ren,"Cube:Vao_Pos","Shader_Pos"), scene(scn), lightType(lt)
{
    if(scene != nullptr){
        scene->addLightCaster(this);
    }
}

chaos::LightCaster::LightType chaos::LightCaster::getLightType(){
    return lightType;
}

void chaos::LightCaster::setLightType(LightType lt){
    lightType = lt;
}

void chaos::LightCaster::setDiffuseStrength(GLfloat diffStr){
    diffuseStrength = diffStr;
}

GLfloat chaos::LightCaster::getDiffuseStrength(){
    return diffuseStrength;
}

void chaos::LightCaster::setSpecularStrength(GLfloat specStr){
    specularStrength = specStr;
}

GLfloat chaos::LightCaster::getSpecularStrength(){
    return specularStrength;
}

/******
    PointLight
*/

chaos::PointLight::PointLight(chaos::Renderer* ren, chaos::Scene* scn)
:LightCaster(ren, scn, chaos::LightCaster::PointLight)
{}

void chaos::PointLight::setupUniforms(chaos::ShaderProgram* shr, chaos::GameObject* obj, GLuint index){
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].position", getPosition());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].color", getColor());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].constant", getConstantAttenuationCoefficient());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].linear", getLinearAttenuationCoefficient());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].quadratic", getQuadraticAttenuationCoefficient());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].diffuseStrength", getDiffuseStrength());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].specularStrength", getSpecularStrength());
}

void chaos::PointLight::setAttenuationCoefficients(GLfloat _constant, GLfloat _linear, GLfloat _quadratic){
    constant = _constant;
    linear = _linear;
    quadratic = _quadratic;
}

GLfloat chaos::PointLight::getConstantAttenuationCoefficient(){
    return constant;
}

GLfloat chaos::PointLight::getLinearAttenuationCoefficient(){
    return linear;
}

GLfloat chaos::PointLight::getQuadraticAttenuationCoefficient(){
    return quadratic;
}



/*******
    DirectionalLight
*/

chaos::DirectionalLight::DirectionalLight(Renderer* ren, Scene* scn)
:LightCaster(ren, scn, chaos::LightCaster::DirectionalLight)
{}

void chaos::DirectionalLight::setupUniforms(ShaderProgram* shr, GameObject* obj, GLuint index){
    shr->setUniform("uniDirLight[" + chaos::toString<GLuint>(index)+ "].color", getColor());
    shr->setUniform("uniDirLight[" + chaos::toString<GLuint>(index)+ "].direction", getDirection());
    shr->setUniform("uniDirLight[" + chaos::toString<GLuint>(index)+ "].diffuseStrength", getDiffuseStrength());
    shr->setUniform("uniDirLight[" + chaos::toString<GLuint>(index)+ "].specularStrength", getSpecularStrength());
}

void chaos::DirectionalLight::setDirection(glm::vec3 dir){
    direction = dir;
}

glm::vec3 chaos::DirectionalLight::getDirection(){
    return direction;
}

