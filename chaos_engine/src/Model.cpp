#include "../include/Model.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Utils.hpp"
#include "../include/Renderer.hpp"
#include "../include/MeshPrefab.hpp"
#include "../include/Camera.hpp"
#include "../include/LightCaster.hpp"

chaos::Model::Model(Renderer*r, MeshPrefab* prefab)
:GameObject(r)
{
    setMesh(prefab);
    shader = renderer->getShader("Shader_Mesh3d");
}

void chaos::Model::draw(){
    shader->run();
    if(!isLighting){
        shader->setUniform("uniColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
    }
    else{
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

void chaos::Model::setMesh(MeshPrefab* prefab){
    meshPrefab = prefab;
    vao = renderer->getVAO("Mesh:Vao_Pos.Uv("+toString(meshPrefab->getMeshId())+")");
}

void chaos::Model::setLightingEnabled(GLboolean enable){
    isLighting = enable;
    if(isLighting){
        shader = renderer->getShader("Shader_Mesh3dLightsOn");
    }
    else{
        shader = renderer->getShader("Shader_Mesh3d");
    }
}
