#ifndef LIGHTING_TEST_HPP
#define LIGHTING_TEST_HPP

#include "../../include/Scene.hpp"
#include "../../include/Camera.hpp"
#include "../../include/primitives.hpp"

class Lighting: public chaos::Scene{
public:
    Lighting(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        cube = new chaos::Cube(renderer);
        cube->setColor(0.2, 0.2, 0.7, 1.0);

        cube->setScale(0.3, 0.3, 0.3);
        //cube->rotateX(0.3);

        cubeLight = new chaos::Cube(renderer);
        cubeLight->setScale(0.1, 0.1, 0.1);
        cubeLight->setPosition(2.0, 0.0, 0.0);

        camera = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        camera->moveZ(5);
        renderer->setActiveCamera(camera);

        window->setRelativeMode(true);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        GLfloat moveSpeed = 0.3;
        if(window->isKeyDown(chaos::KeyboardEvent::KeyH)) cube->moveX(-0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyU)) cube->moveZ(-0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyK)) cube->moveX(0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyJ)) cube->moveZ(0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyA)) camera->processKeyboard(chaos::LEFT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyD)) camera->processKeyboard(chaos::RIGHT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyW)) camera->processKeyboard(chaos::FORWARD, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyS)) camera->processKeyboard(chaos::BACKWARD, deltaTime*moveSpeed);

        window->clearColor(0.7, 0.2, 0.2, 1.0);
        renderer->setCamCombined(camera->getProjectionMatrix()*camera->getViewMatrix());

        cube->rotateY(0.001);

        cube->draw();
        cubeLight->draw();
    }

    void deliverEvent(chaos::Event* event){
        if(event->type == chaos::Event::MouseMotion){
            camera->processMouse(event->motionEvent.relX, -event->motionEvent.relY);
        }
        if (event->type == chaos::Event::KeyDown){
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key9)
                scnManager->setActiveScene("GizmosTest");
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key0)
                scnManager->setActiveScene("VAOnShaders");
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::KeyL){
                cube->setLightingEnabled(!cube->isLightingEnabled());
            }
        }
    }

private:
    chaos::Cube* cube;
    chaos::Cube* cubeLight;
    chaos::Camera* camera;
};

#endif // LIGHTING_TEST_HPP


