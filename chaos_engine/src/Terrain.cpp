#include "../include/Terrain.hpp"
#include "../include/Renderer.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"

chaos::Terrain::Terrain(Renderer* ren, chaos::TerrainPrefab* prefab, std::initializer_list<std::pair<TextureType, Texture*> > listTextures)
:GameObject(ren)
{
    setTerrainMesh(prefab);
    shader = renderer->getShader("Shader_Terrain");
    setColor(0,1,0,1);
    std::vector<Texture*> vecTmp;
    vecTextures.clear();
    vecTextures.resize(textureTypesCount, nullptr);
    for(auto tx: listTextures){
       vecTextures[tx.first] = tx.second;
    }
}

chaos::Terrain::~Terrain(){}


void chaos::Terrain::draw(){
    shader->run();
    if(!isLighting){
        //should be done in loop
        //to be refactored
        if(vecTextures[0] != nullptr){
            vecTextures[0]->bindOnSlot(GL_TEXTURE0);
            shader->setUniform("blendMap", 0);
        }
        if(vecTextures[1] != nullptr){
            vecTextures[1]->bindOnSlot(GL_TEXTURE1);
            shader->setUniform("textureBackground", 1);
        }
        if(vecTextures[2] != nullptr){
            vecTextures[2]->bindOnSlot(GL_TEXTURE2);
            shader->setUniform("textureR", 2);
        }
        if(vecTextures[3] != nullptr){
            vecTextures[3]->bindOnSlot(GL_TEXTURE3);
            shader->setUniform("textureG", 3);
        }
        if(vecTextures[4] != nullptr){
            vecTextures[4]->bindOnSlot(GL_TEXTURE4);
            shader->setUniform("textureB", 4);
        }
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
