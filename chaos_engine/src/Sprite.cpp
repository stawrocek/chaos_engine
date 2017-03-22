#include "../include/Sprite.hpp"
#include "../include/Texture.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/VertexArray.hpp"
#include "../include/Renderer.hpp"

chaos::Sprite::Sprite(Renderer* ren, Texture* tex)
:GameObject(ren,"Rectangle:Vao_Pos.Uv", "Shader_Pos.Uv")
{
    setTexture(tex);
}

void chaos::Sprite::draw(){
    shader->run();
    texture->bind();
    shader->setUniform("uniColor", color);
    shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());

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




