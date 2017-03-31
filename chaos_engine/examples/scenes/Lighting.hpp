#ifndef LIGHTING_TEST_HPP
#define LIGHTING_TEST_HPP

#include "../../include/Scene.hpp"
#include "../../include/Camera.hpp"
#include "../../include/Primitives.hpp"
#include "../../include/Window.hpp"
#include "../../include/LightCaster.hpp"
#include "../../include/MeshPrefab.hpp"
#include "../../include/Model.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Sprite.hpp"

class Lighting: public chaos::Scene{
public:
    Lighting(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        cube = new chaos::Cube(renderer);
        cube->setColor(0.2, 0.2, 0.7, 1.0);

        cube->setScale(2, 2, 2);
        cube->material.setShininess(1024);
        cube->setPosition(-3,-1,-3);
        //cube->rotateX(0.3);

        prefabSkeleton = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/skeleton.obj", "skeleton");
        renderer->addMeshVAO(prefabSkeleton);
        textureSkeleton = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/skeletonUV.png", "uvMap:Skeleton");
        textureBrick = resourceManager->loadResource<chaos::Texture>("files/textures/brick.png", "Brick");

        spriteBrick = new chaos::Sprite(renderer, textureBrick);
        spriteBrick->rotateX(3.1415/2.0);
        spriteBrick->setPosition(0, -1, 0);
        spriteBrick->setScale(10, 0, 10);


        modelSkeleton = new chaos::Model(renderer, prefabSkeleton);
        modelSkeleton->setScale(0.1, 0.1, 0.1);
        modelSkeleton->setPosition(0, -1, 0);
        //modelSkeleton->setPosition(0,2,0);

        light = new chaos::PointLight(renderer, this);
        light->setPosition(2.0, -0.7, 0.0);
        light->setScale(0.1, 0.1, 0.1);
        light->setColor(0.4, 0.1, 0.1, 1);
        light->setAttenuationCoefficients(1.0, 0.09, 0.032);

        light2 = new chaos::PointLight(renderer, this);
        light2->setPosition(-2.0, -0.7, 0.0);
        light2->setScale(0.1, 0.1, 0.1);
        light2->setColor(0.1, 0.1, 0.4, 1);
        light2->setAttenuationCoefficients(1.0, 0.09, 0.032);

        dirLight = new chaos::DirectionalLight(renderer, this);
        dirLight->setColor(0.2, 0.2, 0.2, 1);
        dirLight->setDirection(glm::vec3(-1, -1, 0));
        //dirLight->setDiffuseStrength(5.0);*/

        spotlight = new chaos::Spotlight(renderer, this);
        spotlight->setCutOffCosine(0.92);
        spotlight->setColor(0.5,0.5,0.5,1.0);
        camera = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        camera->moveZ(5);
        renderer->setActiveCamera(camera);

        window->setRelativeMode(true);

        cube->setLightingEnabled(true);
        modelSkeleton->setLightingEnabled(true);
        spriteBrick->setLightingEnabled(true);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        if(window->isTouched(chaos::TouchEvent::ButtonRight)){
            spotlight->setEnabled(true);
        }
    #ifndef ANDROID
        else{
            spotlight->setEnabled(false);
        }
    #endif

        GLfloat moveSpeed = 1.0;
        if(window->isKeyDown(chaos::KeyboardEvent::KeyH)) cube->moveX(-0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyU)) cube->moveZ(-0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyK)) cube->moveX(0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyJ)) cube->moveZ(0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyQ)) spriteBrick->moveY(0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyE)) spriteBrick->moveY(-0.01);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyA)) camera->processKeyboard(chaos::LEFT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyD)) camera->processKeyboard(chaos::RIGHT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyW)) camera->processKeyboard(chaos::FORWARD, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyS)) camera->processKeyboard(chaos::BACKWARD, deltaTime*moveSpeed);

        window->clearColor(0.7, 0.2, 0.2, 1.0);
        renderer->setCamCombined(camera->getProjectionMatrix()*camera->getViewMatrix());

        spriteBrick->draw();

        cube->draw();
        textureSkeleton->bind();
        modelSkeleton->draw();

        light->draw();
        light2->draw();
        spotlight->setPosition(camera->getPosition());
        spotlight->setDirection(camera->getFront());
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
                modelSkeleton->setLightingEnabled(!modelSkeleton->isLightingEnabled());
                spriteBrick->setLightingEnabled(!spriteBrick->isLightingEnabled());
            }
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key1){
                light->setEnabled(!light->isEnabled());
            }
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key2){
                light2->setEnabled(!light2->isEnabled());
            }
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key3){
                dirLight->setEnabled(!dirLight->isEnabled());
            }
        }
    }

private:
    chaos::Cube* cube;
    chaos::Camera* camera;
    chaos::PointLight* light;
    chaos::PointLight* light2;
    chaos::DirectionalLight* dirLight;
    chaos::Spotlight* spotlight;
    chaos::MeshPrefab* prefabSkeleton;
    chaos::Model* modelSkeleton;
    chaos::Texture* textureSkeleton;
    chaos::Texture* textureBrick;
    chaos::Sprite* spriteBrick;
};

#endif // LIGHTING_TEST_HPP


