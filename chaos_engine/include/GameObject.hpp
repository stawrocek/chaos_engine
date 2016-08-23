#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>

#include "Transform.hpp"
#include "Renderer.hpp"

namespace chaos{

class GameObject: public Transform{
public:
    GameObject(Renderer* ren)
    :renderer(ren)
    {}

    virtual ~GameObject(){}

    virtual void draw(){

    }

    Renderer* getRenderer(){
        return renderer;
    }

    void setRenderer(Renderer* ren){
        renderer = ren;
    }

protected:
    Renderer* renderer;
};

}

#endif // GAME_OBJECT_HPP

