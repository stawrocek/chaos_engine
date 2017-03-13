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

        spritePiet->draw();
    }

    void deliverEvent(void* event){
        /*chaos::Event* e = (chaos::Event*)event;
        if(e->key.keysym.sym == SDLK_n){

        }
        if(e->type == SDL_MOUSEMOTION){

        }*/
    }

private:
    chaos::Texture* piet;
    chaos::Sprite* spritePiet;
};

#endif // COLORFUL_TRIANGLES_HPP
