#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "GameObject.hpp"
#include "Renderer.hpp"

namespace chaos{

class Rectangle: public GameObject
{
public:
    Rectangle(std::string s):GameObject(s){};
    virtual ~Rectangle(){};
    virtual void draw(Renderer* ren){
        ren->getShader("Shader_Pos")->setUniform("ourColor", color);
        //to nizej -> przenies viewMatrix do renderera
        /*ren->getShader("Shader_Pos.Uv")->setUniform("mx",mxProj*cam.getViewMatrix()*testTransform.getGlobalTransformMatrix());
        renderer.getShader("Shader_Pos.Uv")->setUniform("tex0", texture1->getId());

        renderer.getVAO("Vao_Pos.Uv")->bind();
        glDrawArrays(GL_TRIANGLES, 0, renderer.getVAO("Vao_Pos.Uv")->countVertices());
        renderer.getVAO("Vao_Pos.Uv")->unbind();*/
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



