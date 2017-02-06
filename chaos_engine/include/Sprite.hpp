#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Export.hpp"

#include "GameObject.hpp"

namespace chaos{

class CHAOS_EXPORT Sprite: public DrawableGameObject{
public:
    Sprite(Renderer* ren, Texture* tex)
    :DrawableGameObject(ren,"Rectangle:Vao_Pos.Uv", "Shader_Pos.Uv")
    {
        setTexture(tex);
    }

    virtual void draw(){
        shader->run();
        texture->bind();
        shader->setUniform("uniColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());

        vao->bind();
        vao->draw(shader);
        vao->unbind();
    }

    void setTexture(Texture* tex){
        texture = tex;
    }

    const Texture* getTexture(){
        return texture;
    }

protected:
    Texture* texture = nullptr;
};

}

#endif //SPRITE_HPP



