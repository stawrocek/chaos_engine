#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "GameObject.hpp"
#include "Renderer.hpp"

namespace chaos{

class Primitive: public GameObject{
public:
    Primitive(Renderer* ren)
    :GameObject(ren)
    {};

    virtual ~Primitive(){};
    virtual void draw()=0;

    glm::vec4 getColor(){
        return color;
    }

    void setColor(glm::vec4 c){
        color = c;
    }

protected:
    glm::vec4 color;
    ShaderProgram* shader = nullptr;
    VertexArray* vao = nullptr;
};

class Rectangle: public Primitive
{
public:
    Rectangle(Renderer* ren):Primitive(ren){
        shader = renderer->getShader("Shader_Pos");
        vao = renderer->getVAO("Vao_Pos");
    };
    virtual ~Rectangle(){};
    virtual void draw(){
        shader->run();
        shader->setUniform("uniColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());

        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vao->countVertices());
        vao->unbind();
    }
};

}

#endif //PRIMITIVES_HPP



