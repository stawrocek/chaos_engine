#ifndef COLORFUL_TRIANGLES_HPP
#define COLORFUL_TRIANGLES_HPP

#include "../../include/Scene.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Sprite.hpp"

class ColorfulTriangles: public chaos::Scene{
public:
    ColorfulTriangles(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        piet = resourceManager->loadResource<chaos::Texture>("files/textures/composition-a-1923-piet-mondrian.png", "piet");
        spritePiet = new chaos::Sprite(renderer, piet);
        spritePiet->setScale(0.33,0.33,0.33);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        window->clearColor(0.2, 0.7, 0.2, 1.0);
        renderer->setCamCombined(glm::mat4(1));

        if(!window->isTouched())
            spritePiet->draw();
        spritePiet->setRotZ(window->inputManager->getMouseX()/100.0);

        if(window->isKeyDown(chaos::KeyboardEvent::KeyX))
            spritePiet->setScale(0.1,0.1,0.1);
        else
            spritePiet->setScale(0.33,0.33,0.33);
    }

    void deliverEvent(chaos::Event* event){
        if (event->type == chaos::Event::KeyDown){
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key9)
                scnManager->setActiveScene("GizmosTest");
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key0)
                scnManager->setActiveScene("VAOnShaders");
        }
    }

private:
    chaos::Texture* piet;
    chaos::Sprite* spritePiet;
};

#endif // COLORFUL_TRIANGLES_HPP
