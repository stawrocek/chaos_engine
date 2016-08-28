#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <fstream>

#include "GameObject.hpp"
#include "MeshPrefab.hpp"

namespace chaos
{
class Model: public DrawableGameObject{
public:
    Model(Renderer*r, MeshPrefab* prefab)
    :DrawableGameObject(r)
    {
        if(shader == nullptr){
            std::cout << "nullptr shader\n";
        }
        if(vao == nullptr){
            std::cout << "nullptr vao\n";
        }
        setMesh(prefab);
        shader = renderer->getShader("Shader_Mesh3d");
        vao = renderer->getVAO("Mesh:Vao_Pos.Uv("+toString(prefab->getMeshId())+")");
        std::cout << "setting mesh vao = " << "Mesh:Vao_Pos.Uv("+toString(prefab->getMeshId())+")" << "\n";
        std::cout << "vao.getId()=" << vao->getId() << "\n";
    }

    virtual void draw(){
        shader->run();
        shader->setUniform("ourColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());

        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vao->countVertices());
        vao->unbind();
    }

    void setMesh(MeshPrefab* prefab){
        meshPrefab = prefab;
    }

protected:
    MeshPrefab* meshPrefab = nullptr;
};


}

#endif //MODEL_HPP



