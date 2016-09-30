#ifndef TANK_HPP
#define TANK_HPP

#include "../include/GameObject.hpp"
#include "../include/primitives.hpp"

using namespace chaos;

namespace tanx{

class Tank: public GameObject{
public:
    Cube turret;
    Cube chassis;

    Tank(Renderer*ren)
    :GameObject(ren), turret(ren), chassis(ren)
    {
        chassis.setColor(0.21f, 0.4f, 0.f, 1.f);
        turret.setColor(0.29f, 0.6f, 0.f, 1.f);
        turret.moveX(1.f);
        turret.moveY(2.f);
        chassis.moveY(1.f);
    }

    void draw(){
        turret.draw();
        chassis.draw();
    }
};

}

#endif // TANK_HPP
