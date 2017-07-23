#include "../include/Terrain.hpp"
#include "../include/Renderer.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"

chaos::Terrain::Terrain(Renderer* ren, chaos::TerrainPrefab* prefab)
:GameObject(ren)
{
    setTerrainMesh(prefab);
    shader = renderer->getShader("Shader_Terrain");
    setColor(0,1,0,1);
}

chaos::Terrain::~Terrain(){}


void chaos::Terrain::draw(){
    shader->run();
    if(!isLighting){
        shader->setUniform("uniColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
    }
    else{
        //to be implemented
    }

    vao->bind();
    vao->draw(shader);
    vao->unbind();
}
void chaos::Terrain::setTerrainMesh(TerrainPrefab* prefab){
    terrainPrefab = prefab;
    vao = renderer->getVAO("Terrain:Vao_Pos("+prefab->getId()+")");
}
