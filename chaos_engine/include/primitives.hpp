#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "GameObject.hpp"
#include "Renderer.hpp"

namespace chaos{

class Rectangle: public GameObject
{
public:
    Rectangle(Renderer* ren):GameObject(ren){};
    virtual ~Rectangle(){};
    virtual void draw(Renderer* ren){
        ren->getShader("Shader_Pos")->run();
        ren->getShader("Shader_Pos")->setUniform("uniColor", color);
        ren->getShader("Shader_Pos")->setUniform("mx",ren->getCamCombined()*getGlobalTransformMatrix());

        ren->getVAO("Vao_Pos")->bind();
        glDrawArrays(GL_TRIANGLES, 0, ren->getVAO("Vao_Pos")->countVertices());
        ren->getVAO("Vao_Pos")->unbind();
    }

    glm::vec4 getColor(){
        return color;
    }

    void setColor(glm::vec4 c){
        color = c;
    }

private:
    glm::vec4 color;
};

}

#endif //PRIMITIVES_HPP



