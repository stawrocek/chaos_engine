#ifndef IMGUITEST_HPP
#define IMGUITEST_HPP

#include "../../include/Scene.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Sprite.hpp"
#include "../../include/ImGUI_Impl_Chaos.hpp"

class ImGUITest: public chaos::Scene{
public:
    ImGUITest(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        rect = new chaos::Rectangle(renderer);
        rect->setScale(0.3, 0.3, 0.3);
        rect->setColor(1.0, 1.0, 0.0, 1.0);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        window->clearColor(0.2, 0.7, 0.2, 1.0);
        renderer->setCamCombined(glm::mat4(1));

        rect->rotateZ(deltaTime);
        rect->draw();
    }

    void deliverEvent(chaos::Event* event){

    }

private:
    chaos::Rectangle* rect=nullptr;
    bool show_test_window = true;
    bool show_another_window = false;
};

#endif // IMGUITEST_HPP
