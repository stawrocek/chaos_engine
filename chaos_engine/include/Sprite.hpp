#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "GameObject.hpp"

namespace chaos{

class Sprite: public DrawableGameObject{
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
        glDrawArrays(GL_TRIANGLES, 0, vao->countVertices());
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



