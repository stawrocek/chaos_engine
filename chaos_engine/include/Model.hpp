#ifndef MODEL_HPP
#define MODEL_HPP

#include "Export.hpp"

#include <string>
#include <fstream>

#include "GameObject.hpp"
#include "MeshPrefab.hpp"

namespace chaos
{
class CHAOS_EXPORT Model: public DrawableGameObject{
public:
    Model(Renderer*r, MeshPrefab* prefab)
    :DrawableGameObject(r)
    {
        setMesh(prefab);
        shader = renderer->getShader("Shader_Mesh3d");
    }

    virtual void draw(){
        shader->run();
        shader->setUniform("uniColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());
        vao->bind();
        vao->draw(shader);
        vao->unbind();
    }

    void setMesh(MeshPrefab* prefab){
        meshPrefab = prefab;
        vao = renderer->getVAO("Mesh:Vao_Pos.Uv("+toString(meshPrefab->getMeshId())+")");
    }

protected:
    MeshPrefab* meshPrefab = nullptr;
};


}

#endif //MODEL_HPP



