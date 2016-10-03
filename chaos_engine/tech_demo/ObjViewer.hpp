#ifndef OBJ_VIEWER_HPP
#define OBJ_VIEWER_HPP

#include <string>

#include "../include/Scene.hpp"
#include "../include/Model.hpp"
#include "../include/MeshPrefab.hpp"
#include "../include/Camera.hpp"
#include "../include/BitmapFontSprite.hpp"
#include "../include/Sprite.hpp"

class ObjViewer: public chaos::Scene{
public:
    ObjViewer(std::string _name)
    :Scene(_name)
    {}

    virtual ~ObjViewer(){
        delete cam;
        delete actModel;
        delete textLeft;
        delete textRight;
        delete spriteBackground;
    }

    virtual void onSceneLoadToMemory(){
        chestPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/Chest2.obj", "chest");
        renderer->addMeshVAO(chestPrefab);
        chestTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/chestUV.png", "uvMap:Chest");
        backgroundTexture = resourceManager->loadResource<chaos::Texture>("files/textures/brick.jpg", "background");
        bitmapFont = resourceManager->getResource<chaos::BitmapFont>("Calibri");

        actModel = new chaos::Model(renderer, chestPrefab);
        actModel->setScale(.1f, .1f, .1f);
        actTexture = resourceManager->getResource<chaos::Texture>("uvMap:Chest");
        cam = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        cam->moveZ(21.f);
        cam->moveY(3.5f);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        textLeft = new chaos::BitmapFontSprite(renderer, bitmapFont,    "press [key] to change shader\n"
                                                                        "[e] -> \"explosion\"\n"
                                                                        "[v] -> normal vectors visualizer\n"
                                                                        "[n] -> standard display\n");
        textLeft->setFitToScreen(true);
        textLeft->moveY(2.0-64.f/window->getStyle().height);

        textRight = new chaos::BitmapFontSprite(renderer, bitmapFont,   "source code:\n"
                                                                        "https://github.com/stawrocek/chaos_engine\n"
                                                                        "press [g] to visit\n");
        textRight->setFitToScreen(true);
        textRight->moveY(128.f/window->getStyle().height);

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

        renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());
        actModel->setRotY(SDL_GetTicks()/2000.f);
        clearWindow(0.2, 0.2, 0.2, 1.0);
        spriteBackground->draw();
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

            textLeft->draw();
            textRight->draw();
        }

        cam->update();
    }
    virtual void deliverEvent(chaos::Event& e){
        if(e.getChar() == 'n'){
            renderMode=0;
        }
        if(e.getChar() == 'e'){
            renderMode=1;
        }
        if(e.getChar() == 'v'){
            renderMode=2;
        }
        if(e.getChar() == 'g'){
            launchGithub();
        }

        if(e.type == SDL_MOUSEMOTION) {
            cam->processMouse(e.motion.xrel, -e.motion.yrel);
        }
    }

    void launchGithub(){
        #ifdef _WIN32
            system("start https://github.com/stawrocek/chaos_engine");
        #elif __APPLE__
            system("open https://github.com/stawrocek/chaos_engine");
        #elif __linux__
            std::string browser = getenv("BROWSER");
            std::string url = "https://github.com/stawrocek/chaos_engine";
            if(browser == "") return;
            char *args[3];
            args[0] = (char*)browser.c_str();
            args[1] = (char*)url.c_str();
            args[2] = 0;
            pid_t pid = fork();
            if(!pid)
            execvp(browser.c_str(), args);
        #endif
    }

private:
    chaos::Model* actModel = nullptr;
    chaos::Texture* actTexture = nullptr;
    chaos::BitmapFontSprite* textLeft = nullptr;
    chaos::BitmapFontSprite* textRight = nullptr;
    chaos::Sprite* spriteBackground=nullptr;


    chaos::Texture* backgroundTexture;
    chaos::Texture* chestTexture;
    chaos::MeshPrefab* chestPrefab;
    chaos::BitmapFont* bitmapFont;

    chaos::Camera* cam;
    int renderMode = 0; //0->normal, 1->explosion shader, 2->normals shader
    GLfloat moveSpeed=5.f;
};

#endif // OBJ_VIEWER_HPP


