#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Export.hpp"

#include "GameObject.hpp"

namespace chaos{

class Texture;

class Renderer;

class CHAOS_EXPORT Sprite: public GameObject{
public:
    Sprite(Renderer* ren, Texture* tex);
    virtual void draw();
    void setTexture(Texture* tex);
    Texture* getTexture();

protected:
    Texture* texture = nullptr;
};

}

#endif //SPRITE_HPP



