#include "../include/LightCaster.hpp"

#include "../include/Scene.hpp"
#include "../include/Utils.hpp"

chaos::LightCaster::LightCaster(chaos::Renderer * ren, chaos::Scene* scn)
:GameObject(ren,"Cube:Vao_Pos","Shader_Pos"), scene(scn)
{
    if(scene != nullptr){
        scene->addLightCaster(this);
    }
}

chaos::PointLight::PointLight(chaos::Renderer* ren, chaos::Scene* scn)
:LightCaster(ren, scn)
{

}

void chaos::PointLight::setupUniforms(chaos::ShaderProgram* shr, chaos::GameObject* obj, GLuint index){
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].position", getPosition());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].color", getColor());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].constant", getConstantAttenuationCoefficient());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].linear", getLinearAttenuationCoefficient());
    shr->setUniform("uniPointLight[" + chaos::toString<GLuint>(index)+ "].quadratic", getQuadraticAttenuationCoefficient());
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
