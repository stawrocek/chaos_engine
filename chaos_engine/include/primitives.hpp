#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "Export.hpp"

#include "GameObject.hpp"

namespace chaos{

class Renderer;

class CHAOS_EXPORT Rectangle: public GameObject
{
public:
    Rectangle(Renderer* ren);
};

class CHAOS_EXPORT Cube: public GameObject
{
public:
    Cube(Renderer* ren);
    virtual void setLightingEnabled(GLboolean enable);
};

class CHAOS_EXPORT Circle: public GameObject
{
public:
    Circle(Renderer* ren);
};

}

#endif //PRIMITIVES_HPP



