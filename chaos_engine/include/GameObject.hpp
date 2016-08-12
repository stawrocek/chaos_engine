#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>

#include "Transform.hpp"

namespace chaos{

class GameObject: public Transform{
public:
    GameObject(){}
    GameObject(std::string _name)
    :name(_name)
    {}

    virtual ~GameObject(){}
    std::string getName(){
        return name;
    }
protected:
    std::string name;
};

}

#endif // GAME_OBJECT_HPP

