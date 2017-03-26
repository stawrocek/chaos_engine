#ifndef LIGHTING_TEST_HPP
#define LIGHTING_TEST_HPP

#include "../../include/Scene.hpp"
#include "../../include/Camera.hpp"
#include "../../include/primitives.hpp"
#include "../../include/Window.hpp"
#include "../../include/LightCaster.hpp"

class Lighting: public chaos::Scene{
public:
    Lighting(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        cube = new chaos::Cube(renderer);
        cube->setColor(0.2, 0.2, 0.7, 1.0);

        cube->setScale(0.3, 0.3, 0.3);
        cube->material.setShininess(1024);
        //cube->rotateX(0.3);

        /*light = new chaos::PointLight(renderer, this);
        light->setPosition(2.0, 0.0, 0.0);
        light->setScale(0.05, 0.05, 0.05);
        light->setColor(1, 1, 1, 1);
        light->setAttenuationCoefficients(1.0, 0.09, 0.032);

        light2 = new chaos::PointLight(renderer, this);
        light2->setPosition(-2.0, 0.0, 0.0);
        light2->setScale(0.05, 0.05, 0.05);
        light2->setColor(1, 0, 0, 1);
        light2->setAttenuationCoefficients(1.0, 0.09, 0.032);*/

        dirLight = new chaos::DirectionalLight(renderer, this);
        dirLight->setColor(1, 1, 0, 1);
        dirLight->setDirection(glm::vec3(-1, -1, 0));
        dirLight->setDiffuseStrength(0.5);

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
        //light->draw();
        //light2->draw();
        //dirLight->draw();
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
    chaos::Camera* camera;
    //chaos::PointLight* light;
    //chaos::PointLight* light2;
    chaos::DirectionalLight* dirLight;
};

#endif // LIGHTING_TEST_HPP


