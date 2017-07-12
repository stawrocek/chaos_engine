#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP

/*
    Basic example of Transforms parenting
*/
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "../../include/Scene.hpp"
#include "../../include/Primitives.hpp"
#include "../../include/Camera.hpp"
#include "../../include/CubeMap.hpp"
#include "../../include/Skybox.hpp"
#include "../../include/FBO.hpp"
#include "../../include/Sprite.hpp"

class Transforms: public chaos::Scene{
public:
    Transforms(std::string _name)
    :Scene(_name)
    {}

    ~Transforms(){
        for(int i = 0; i < vecCubes.size(); i++){
            delete vecCubes[i];
        }
    }

    void onSceneLoadToMemory(){
        srand(time(NULL));
        vecCubes.resize(10);
        for(int i = 0; i < 10; i++){
            vecCubes[i] = new chaos::Cube(renderer);
            vecCubes[i]->moveX(2*i);
            vecCubes[i]->setColor(i/10.0, 0, 0, 1);
            if(i != 0){
                vecCubes[i]->setParent(vecCubes[i-1]);
            }
        }
        vecCubes.front()->setScale(0.01, 0.01, 0.01);

        camera = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        camera->moveZ(1.0);
        window->setRelativeMode(true);

        //skyboxTexture = resourceManager->loadResource("files/textures/skyboxes/skybox1/",
        //                {"right.jpg","left.jpg","top.jpg","bottom.jpg","back.jpg","front.jpg"},"skybox1");
        skyboxTexture = resourceManager->loadResource("files/textures/",
                        {"brick.png","brick.png","brick.png","brick.png","brick.png","brick.png"},"skybox1");
        skybox = new chaos::Skybox(renderer, skyboxTexture);
        skybox->rotateZ(3.1415);

        fbo = new chaos::FBO(window->getGLDrawableWidth(), window->getGLDrawableHeight(), 1);
        fboTexture = fbo->getTexture(0);
        fboSprite = new chaos::Sprite(renderer, fboTexture);
        //fboSprite->setScale(0.2, 0.2, 0.2);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        if(window->isKeyDown(chaos::KeyboardEvent::KeyA))
            camera->processKeyboard(chaos::LEFT, deltaTime*cameraMoveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyD))
            camera->processKeyboard(chaos::RIGHT, deltaTime*cameraMoveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyW))
            camera->processKeyboard(chaos::FORWARD, deltaTime*cameraMoveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyS))
            camera->processKeyboard(chaos::BACKWARD, deltaTime*cameraMoveSpeed);
        for(int i = 0; i < vecCubes.size(); i++){
            if(i%3 == 0)
                vecCubes[i]->rotateZ(rotSpeed);
            if(i%3 == 1)
                vecCubes[i]->rotateY(rotSpeed);
            if(i%3 == 2)
                vecCubes[i]->rotateX(rotSpeed);
        }
        renderer->setCamCombined(camera);
        fbo->bind();
        window->clearColor(0.2, 0.7, 0.2, 1.0);
        skybox->draw();
        for(auto cb: vecCubes)
            cb->draw();
        fbo->unbind();
        window->clearColor(0.2, 0.7, 0.2, 1.0);
        skybox->draw();
        for(auto cb: vecCubes)
            cb->draw();
        //if(window->isKeyDown(chaos::KeyboardEvent::KeyP))
            fboSprite->draw();
    }

    void deliverEvent(chaos::Event* event){
        if(event->type == chaos::Event::MouseMotion){
            camera->processMouse(event->motionEvent.relX, -event->motionEvent.relY);
        }
    }

private:
    std::vector<chaos::Cube*> vecCubes;
    chaos::Camera* camera=nullptr;
    GLfloat cameraMoveSpeed=0.1f;
    GLfloat rotSpeed = 0.001;
    chaos::CubeMap* skyboxTexture=nullptr;
    chaos::Skybox* skybox=nullptr;
    chaos::FBO* fbo=nullptr;
    chaos::Texture* fboTexture=nullptr;
    chaos::Sprite* fboSprite=nullptr;
};

#endif // VAONSHADERS_HPP


