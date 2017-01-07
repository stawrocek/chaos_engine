#ifndef GIZMOS_HPP
#define GIZMOS_HPP

#include <string>

#include "../include/Scene.hpp"
#include "../include/Model.hpp"
#include "../include/MeshPrefab.hpp"
#include "../include/Camera.hpp"
#include "../include/BitmapFontSprite.hpp"
#include "../include/Sprite.hpp"

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
        backgroundTexture = resourceManager->loadResource<chaos::Texture>("files/textures/brick.jpg", "background");
        bitmapFont = resourceManager->getResource<chaos::BitmapFont>("Calibri");

        actModel = new chaos::Model(renderer, skeletonPrefab);
        actModel->setScale(0.2,0.2,0.2);
        actTexture = skeletonTexture;
        cam = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        cam->moveY(3.5f);
        cam->moveZ(21.f);
        SDL_SetRelativeMouseMode(SDL_TRUE);

        spriteBackground = new chaos::Sprite(renderer, backgroundTexture);
        spriteBackground->rotateX(3.1415f/2.f);
        spriteBackground->setScale(20.f, 20.f, 20.f);
    }

    virtual void onSceneActivate(){};

    virtual void draw(GLfloat deltaTime){
        if(inputHandler->isKeyDown('a'))
            cam->processKeyboard(chaos::LEFT, deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('d'))
            cam->processKeyboard(chaos::RIGHT, deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('w'))
            cam->processKeyboard(chaos::FORWARD, deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('s'))
            cam->processKeyboard(chaos::BACKWARD, deltaTime*moveSpeed);

        /*if(inputHandler->isKeyDown('k'))actModel->moveX(deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('h'))actModel->moveX(-deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('u'))actModel->moveY(deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('j'))actModel->moveY(-deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('o'))actModel->moveZ(deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('l'))actModel->moveZ(-deltaTime*moveSpeed);*/

        glm::vec3 f = actModel->getFront(), u = actModel->getUp(), r = actModel->getRight();

        if(inputHandler->isKeyDown('k'))actModel->translate(r*deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('h'))actModel->translate(r*-deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('u'))actModel->translate(u*deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('j'))actModel->translate(u*-deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('o'))actModel->translate(f*deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('l'))actModel->translate(f*-deltaTime*moveSpeed);

        if(inputHandler->isKeyDown('b'))actModel->rotateX(-deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('n'))actModel->rotateX(deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('y'))actModel->rotateY(-deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('i'))actModel->rotateY(deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('c'))actModel->rotateZ(-deltaTime*moveSpeed);
        if(inputHandler->isKeyDown('v'))actModel->rotateZ(deltaTime*moveSpeed);

        renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());
        //renderer->setCamCombined(glm::mat4());
        //actModel->setRotY(SDL_GetTicks()/2000.f);
        clearWindow(0.2, 0.2, 0.2, 1.0);
        spriteBackground->draw();
        if(actModel != nullptr){
            if(renderMode==0){
                actTexture->bind();
                actModel->draw();
            }
        }
        actModel->drawGizmo();
    }
    virtual void deliverEvent(chaos::Event& e){
        if(e.type == SDL_MOUSEMOTION) {
            cam->processMouse(e.motion.xrel, -e.motion.yrel);
        }
    }

private:
    chaos::Model* actModel = nullptr;
    chaos::Texture* actTexture = nullptr;
    chaos::Sprite* spriteBackground=nullptr;
    chaos::BitmapFont* bitmapFont=nullptr;

    chaos::Texture* backgroundTexture;
    chaos::Texture* skeletonTexture;
    chaos::MeshPrefab* skeletonPrefab;
    chaos::Camera* cam;
    GLuint renderMode = 0; //0->normal, 1->explosion shader, 2->normals shader
    GLfloat moveSpeed=1.f;
};

#endif // GIZMOS_HPP



