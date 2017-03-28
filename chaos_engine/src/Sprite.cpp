#include "../include/Sprite.hpp"
#include "../include/Texture.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"
#include "../include/Renderer.hpp"
#include "../include/Camera.hpp"
#include "../include/LightCaster.hpp"

chaos::Sprite::Sprite(Renderer* ren, Texture* tex)
:GameObject(ren,"Rectangle:Vao_Pos.Uv", "Shader_Pos.Uv")
{
    setTexture(tex);
}

void chaos::Sprite::draw(){
    shader->run();
    if(!isLighting){
        texture->bind();
        shader->setUniform("uniColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
    }
    else{
        texture->bind();
        glm::mat3x3 modelMatrix3(getGlobalTransformMatrix());
        glm::mat3x3 normalMatrix = glm::inverseTranspose(modelMatrix3);
        shader->setUniform("normalMatrix", normalMatrix);
        shader->setUniform("model", getGlobalTransformMatrix());
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
        shader->setUniform("uniViewPos", renderer->getActiveCamera()->getPosition());

        shader->setUniform("ambientStrength", 0.0f);
        shader->setUniform("ambientColor", glm::vec4(0, 1, 0, 1));

        shader->setUniform("uniMaterial.diffuseColor", material.getDiffuseColor());
        shader->setUniform("uniMaterial.specularColor", material.getSpecularColor());
        shader->setUniform("uniMaterial.shininess", material.getShininess());
        shader->setUniform("uniObjectColor", getColor());


        GLuint pointLightCtr=0, dirLightCtr=0, spotlightCtr=0;
        for(GLuint i = 0; i < renderer->getLightCastersVector()->size(); i++){
            if(renderer->getLightCastersVector()->at(i)->isEnabled() && renderer->getLightCastersVector()->at(i)->getLightType() == LightCaster::PointLight){
                renderer->getLightCastersVector()->at(i)->setupUniforms(shader, this, pointLightCtr);
                pointLightCtr++;
            }
            if(renderer->getLightCastersVector()->at(i)->isEnabled() && renderer->getLightCastersVector()->at(i)->getLightType() == LightCaster::DirectionalLight){
                renderer->getLightCastersVector()->at(i)->setupUniforms(shader, this, dirLightCtr);
                dirLightCtr++;
            }
            if(renderer->getLightCastersVector()->at(i)->isEnabled() && renderer->getLightCastersVector()->at(i)->getLightType() == LightCaster::Spotlight){
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

void chaos::Sprite::setTexture(Texture* tex){
    texture = tex;
}

chaos::Texture* chaos::Sprite::getTexture(){
    return texture;
}

void chaos::Sprite::setLightingEnabled(GLboolean enable){
    isLighting = enable;
    if(isLighting){
        shader = renderer->getShader("Shader_Mesh3dLightsOn");
        vao = renderer->getVAO("Rectangle:Vao_Pos.Normal.Uv");
    }
    else{
        shader = renderer->getShader("Shader_Mesh3d");
        vao = renderer->getVAO("Rectangle:Vao_Pos.Uv");
    }
}



