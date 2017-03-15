#ifndef GIZMOS_HPP
#define GIZMOS_HPP

#include <string>

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
        if(window->isKeyDown(SDLK_a))
            cam->processKeyboard(chaos::LEFT, deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_d))
            cam->processKeyboard(chaos::RIGHT, deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_w))
            cam->processKeyboard(chaos::FORWARD, deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_s))
            cam->processKeyboard(chaos::BACKWARD, deltaTime*moveSpeed);

        glm::vec3 f = actModel->getFront(), u = actModel->getUp(), r = actModel->getRight();

        if(window->isKeyDown(SDLK_k))actModel->translate(r*deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_h))actModel->translate(r*-deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_u))actModel->translate(u*deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_j))actModel->translate(u*-deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_o))actModel->translate(f*deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_l))actModel->translate(f*-deltaTime*moveSpeed);

        if(window->isKeyDown(SDLK_n))actModel->rotateX(-deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_n))actModel->rotateX(deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_y))actModel->rotateY(-deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_i))actModel->rotateY(deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_c))actModel->rotateZ(-deltaTime*moveSpeed);
        if(window->isKeyDown(SDLK_v))actModel->rotateZ(deltaTime*moveSpeed);

        renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());
        clearWindow(0.2, 0.2, 0.2, 1.0);
        spriteBackground->draw();
        if(actModel != nullptr){
            if(renderMode==0){
                actTexture->bind();
                actModel->draw();
            }
        }
        actModel->drawGizmo(10);
    }
    virtual void deliverEvent(void* event){
        SDL_Event* e = (SDL_Event*)event;
        if(e->type == SDL_MOUSEMOTION) {
            cam->processMouse(e->motion.xrel, -e->motion.yrel);
        }
        else if (e->type == SDL_KEYDOWN){
            if(e->key.keysym.sym == SDLK_9)
                scnManager->setActiveScene("VAOnShaders");
            if(e->key.keysym.sym == SDLK_0)
                scnManager->setActiveScene("ObjViewer");
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



