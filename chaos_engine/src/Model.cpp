#include "../include/Model.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Utils.hpp"
#include "../include/Renderer.hpp"
#include "../include/MeshPrefab.hpp"

chaos::Model::Model(Renderer*r, MeshPrefab* prefab)
:GameObject(r)
{
    setMesh(prefab);
    shader = renderer->getShader("Shader_Mesh3d");
}

void chaos::Model::draw(){
    shader->run();
    shader->setUniform("uniColor", color);
    shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
    vao->bind();
    vao->draw(shader);
    vao->unbind();
}

void chaos::Model::setMesh(MeshPrefab* prefab){
    meshPrefab = prefab;
    vao = renderer->getVAO("Mesh:Vao_Pos.Uv("+toString(meshPrefab->getMeshId())+")");
}
