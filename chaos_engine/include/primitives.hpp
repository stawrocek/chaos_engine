#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "Export.hpp"

#include "GameObject.hpp"
#include "Renderer.hpp"

namespace chaos{

class CHAOS_EXPORT Rectangle: public DrawableGameObject
{
public:
    Rectangle(Renderer* ren):DrawableGameObject(ren, "Rectangle:Vao_Pos", "Shader_Pos"){
    }
};

class CHAOS_EXPORT Cube: public DrawableGameObject
{
public:
    Cube(Renderer* ren):DrawableGameObject(ren,"Cube:Vao_Pos","Shader_Pos"){

    }
};

class CHAOS_EXPORT Circle: public DrawableGameObject
{
public:
    Circle(Renderer* ren):DrawableGameObject(ren,"Circle:Vao_Pos","Shader_Pos"){
    }
};

}

#endif //PRIMITIVES_HPP



