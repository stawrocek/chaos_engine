#ifndef SCENE2_HPP
#define SCENE2_HPP

#include <string>

#include "Scene.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"

class Scene2: public chaos::Scene{
public:
    Scene2(std::string _name)
    :Scene(_name)
    {
        std::cout << "Constructor of Scene2\n";
    }

    virtual ~Scene2(){
        std::cout << "Destructor of Scene2\n";
    }

    virtual void onSceneActivate(){
        std::cout << "Scene2::onSceneActivate()\n";
    };
    virtual void update(GLfloat deltaTime){
    }
    virtual void draw(GLfloat deltaTime){
        clearWindow(0.0, 1.0, 0.0, 1.0);
    }
    virtual void deliverEvent(chaos::Event& e){
    }
    virtual void onSceneDeactivate(){
        std::cout << "Scene2::onSceneDeactivate()\n";
    }
private:
    chaos::Camera camera;
};

#endif // SCENE2_HPP
