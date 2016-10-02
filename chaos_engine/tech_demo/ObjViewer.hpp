#ifndef OBJ_VIEWER_HPP
#define OBJ_VIEWER_HPP

#include <string>

#include "../include/Scene.hpp"
#include "../include/Model.hpp"
#include "../include/MeshPrefab.hpp"
#include "../include/Camera.hpp"

class ObjViewer: public chaos::Scene{
public:
    ObjViewer(std::string _name)
    :Scene(_name)
    {}

    virtual ~ObjViewer(){
        delete cam;
        delete actModel;
    }

    virtual void onSceneLoadToMemory(){
        swordPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/sword.obj", "sword");
        chestPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/Chest2.obj", "chest");
        renderer->addMeshVAO(swordPrefab);
        renderer->addMeshVAO(chestPrefab);
        swordTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/swordUV.png", "uvMap:Sword");
        chestTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/chestUV.png", "uvMap:Chest");

        actModel = new chaos::Model(renderer, chestPrefab);
        actModel->setScale(.1f, .1f, .1f);
        actTexture = resourceManager->getResource<chaos::Texture>("uvMap:Chest");
        cam = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), 800.f/600.f, 0.1f, 100.0f));
        cam->moveZ(21.f);
        cam->moveY(3.5f);
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }

    virtual void onSceneActivate(){};

    virtual void draw(GLfloat deltaTime){
        if(inputHandler->isKeyDown('h'))
            cam->processKeyboard(chaos::LEFT, deltaTime);
        if(inputHandler->isKeyDown('k'))
            cam->processKeyboard(chaos::RIGHT, deltaTime);
        if(inputHandler->isKeyDown('u'))
            cam->processKeyboard(chaos::FORWARD, deltaTime);
        if(inputHandler->isKeyDown('j'))
            cam->processKeyboard(chaos::BACKWARD, deltaTime);


        renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());
        actModel->rotateY(deltaTime/2.f);
        clearWindow(1.0, 0.0, 0.0, 1.0);
        if(actModel != nullptr){
            if(renderMode==0){
                actModel->setShader("Shader_Mesh3d");
                actTexture->bind();
                actModel->draw();
            }
            if(renderMode == 1){
                GLfloat currTime = window->getRunningTimeAsSeconds();
                actModel->setShader("Shader_Mesh3d#Explosion");
                actModel->getShader()->run();
                actModel->getShader()->setUniform("time", currTime);
                actTexture->bind();
                actModel->draw();
            }
            if(renderMode == 2){
                renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());
                actTexture->bind();
                actModel->setShader("Shader_Mesh3d#Normals");
                actModel->getShader()->run();
                actModel->getShader()->setUniform("mxViewModel", cam->getViewMatrix()*actModel->getGlobalTransformMatrix());
                actModel->draw();
                renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());
                actModel->setShader("Shader_Mesh3d");
                actModel->draw();
            }
        }

        cam->update();
    }
    virtual void deliverEvent(chaos::Event& e){
        if(e.getChar() == 'n'){
            renderMode=0;
        }
        if(e.getChar() == 'g'){
            renderMode=1;
        }
        if(e.getChar() == 'v'){
            renderMode=2;
        }
    }

private:
    chaos::Model* actModel = nullptr;
    chaos::Texture* actTexture = nullptr;

    chaos::Texture* swordTexture;
    chaos::Texture* chestTexture;
    chaos::MeshPrefab* swordPrefab;
    chaos::MeshPrefab* chestPrefab;

    chaos::Camera* cam;

    int renderMode = 0; //0->normal, 1->explosion shader, 2->normals shader
};

#endif // OBJ_VIEWER_HPP


