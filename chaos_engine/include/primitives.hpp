#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "Export.hpp"

#include "GameObject.hpp"
#include "Renderer.hpp"

namespace chaos{

class CHAOS_EXPORT Rectangle: public GameObject
{
public:
    Rectangle(Renderer* ren):GameObject(ren, "Rectangle:Vao_Pos", "Shader_Pos"){
    }
};

class CHAOS_EXPORT Cube: public GameObject
{
public:
    Cube(Renderer* ren):GameObject(ren,"Cube:Vao_Pos","Shader_Pos"){

    }

    virtual void setLightingEnabled(GLboolean enable){
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
};

class CHAOS_EXPORT Circle: public GameObject
{
public:
    Circle(Renderer* ren):GameObject(ren,"Circle:Vao_Pos","Shader_Pos"){
    }
};

}

#endif //PRIMITIVES_HPP



