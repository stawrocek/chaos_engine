#include "../include/Primitives.hpp"

#include "../include/Renderer.hpp"


chaos::Rectangle::Rectangle(Renderer* ren):GameObject(ren, "Rectangle:Vao_Pos", "Shader_Pos"){

}

chaos::Cube::Cube(Renderer* ren):GameObject(ren,"Cube:Vao_Pos","Shader_Pos"){

}

void chaos::Cube::setLightingEnabled(GLboolean enable){
    isLighting = enable;
    if(isLighting){
        vao = renderer->getVAO("Cube:Vao_Pos.Norm");
        shader = renderer->getShader("Shader_Pos.Norm");
    }
    else{
        vao = renderer->getVAO("Cube:Vao_Pos");
        shader = renderer->getShader("Shader_Pos");
    }
}


chaos::Circle::Circle(Renderer* ren):GameObject(ren,"Circle:Vao_Pos","Shader_Pos"){

}


