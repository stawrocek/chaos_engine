#ifndef GIZMOS_HPP
#define GIZMOS_HPP

#include <string>
#include <cstdlib>

#include "../../include/Scene.hpp"
#include "../../include/Model.hpp"
#include "../../include/MeshPrefab.hpp"
#include "../../include/Camera.hpp"
#include "../../include/BitmapFontSprite.hpp"
#include "../../include/BitmapFontSprite.hpp"
#include "../../include/Sprite.hpp"

class GizmosTest: public chaos::Scene{
public:
    GizmosTest(std::string _name)
    :Scene(_name)
    {}

    virtual ~GizmosTest(){

    }

    virtual void onSceneLoadToMemory(){
        skeletonPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/skeleton.obj", "skeleton");
        renderer->addMeshVAO(skeletonPrefab);
        skeletonTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/skeletonUV.png", "uvMap:Skeleton");
        backgroundTexture = resourceManager->loadResource<chaos::Texture>("files/textures/brick.png", "background");
        //bitmapFont = resourceManager->getResource<chaos::BitmapFont>("Calibri");

        actModel = new chaos::Model(renderer, skeletonPrefab);
        actModel->setScale(0.2,0.2,0.2);
        actTexture = skeletonTexture;
        cam = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        cam->moveY(3.5f);
        cam->moveZ(21.f);
        window->setRelativeMode(true);
        spriteBackground = new chaos::Sprite(renderer, backgroundTexture);
        spriteBackground->rotateX(3.1415f/2.f);
        spriteBackground->setScale(20.f, 20.f, 20.f);
    }

    virtual void onSceneActivate(){};

    virtual void draw(GLfloat deltaTime){
        if(window->isKeyDown(chaos::KeyboardEvent::KeyA))
            cam->processKeyboard(chaos::LEFT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyD))
            cam->processKeyboard(chaos::RIGHT, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyW))
            cam->processKeyboard(chaos::FORWARD, deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyS))
            cam->processKeyboard(chaos::BACKWARD, deltaTime*moveSpeed);

        glm::vec3 f = actModel->getFront(), u = actModel->getUp(), r = actModel->getRight();

        if(window->isKeyDown(chaos::KeyboardEvent::KeyK))actModel->translate(r*deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyH))actModel->translate(r*-deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyU))actModel->translate(u*deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyJ))actModel->translate(u*-deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyO))actModel->translate(f*deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyL))actModel->translate(f*-deltaTime*moveSpeed);

        if(window->isKeyDown(chaos::KeyboardEvent::KeyN))actModel->rotateX(-deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyM))actModel->rotateX(deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyY))actModel->rotateY(-deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyI))actModel->rotateY(deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyC))actModel->rotateZ(-deltaTime*moveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyV))actModel->rotateZ(deltaTime*moveSpeed);

        if(window->isTouched()){
            actModel->setColor(((double) rand() / (RAND_MAX)),((double) rand() / (RAND_MAX)),((double) rand() / (RAND_MAX))
                               ,((double) rand() / (RAND_MAX)));
        }


        renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());
        clearWindow(0.2, 0.2, 0.2, 1.0);
        spriteBackground->draw();
        if(actModel != nullptr){
            if(renderMode==0){
                actTexture->bind();
                actModel->draw();
            }
        }
        //actModel->drawGizmo();
    }
    virtual void deliverEvent(chaos::Event* event){
        if(event->type == chaos::Event::MouseMotion){
            cam->processMouse(event->motionEvent.relX, -event->motionEvent.relY);
        }
        if (event->type == chaos::Event::KeyDown){
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key9)
                scnManager->setActiveScene("VAOnShaders");
            if(event->keyEvent.keyCode == chaos::KeyboardEvent::Key0)
                scnManager->setActiveScene("ColorfulTriangles");
        }
    }

private:
    chaos::Model* actModel = nullptr;
    chaos::Texture* actTexture = nullptr;
    chaos::Sprite* spriteBackground=nullptr;
    //chaos::BitmapFont* bitmapFont=nullptr;

    chaos::Texture* backgroundTexture;
    chaos::Texture* skeletonTexture;
    chaos::MeshPrefab* skeletonPrefab;
    chaos::Camera* cam;
    GLuint renderMode = 0; //0->normal, 1->explosion shader, 2->normals shader
    GLfloat moveSpeed=1.f;
};

#endif // GIZMOS_HPP



