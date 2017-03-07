#ifndef OBJ_VIEWER_HPP
#define OBJ_VIEWER_HPP

#include <string>

#include "../../include/Scene.hpp"
#include "../../include/Model.hpp"
#include "../../include/MeshPrefab.hpp"
#include "../../include/Camera.hpp"
#include "../../include/BitmapFontSprite.hpp"
#include "../../include/Sprite.hpp"

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
        chestPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/Chest3.obj", "chest");
        skeletonPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/skeleton.obj", "skeleton");
        demonPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/demon.obj", "demon");
        mechPrefab = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/Mech.obj", "mech");
        renderer->addMeshVAO(chestPrefab);
        renderer->addMeshVAO(skeletonPrefab);
        renderer->addMeshVAO(demonPrefab);
        renderer->addMeshVAO(mechPrefab);

        #ifdef GEOMETRY_SHADER_ENABLED
        renderer->addShader({ std::make_pair("examples/shaders/Model3dExplosion.vs", GL_VERTEX_SHADER),
                    std::make_pair("examples/shaders/Model3dExplosion.gs", GL_GEOMETRY_SHADER),
                    std::make_pair("examples/shaders/Model3dExplosion.fs", GL_FRAGMENT_SHADER)}, "Shader_Mesh3d#Explosion");

        renderer->addShader({ std::make_pair("examples/shaders/Model3dNormals.vs", GL_VERTEX_SHADER),
                    std::make_pair("examples/shaders/Model3dNormals.gs", GL_GEOMETRY_SHADER),
                    std::make_pair("examples/shaders/Model3dNormals.fs", GL_FRAGMENT_SHADER)}, "Shader_Mesh3d#Normals");
        renderer->addShader({ std::make_pair("examples/shaders/Model3dExplosion.vs", GL_VERTEX_SHADER),
                    std::make_pair("examples/shaders/Model3dRandom.gs", GL_GEOMETRY_SHADER),
                    std::make_pair("examples/shaders/Model3dExplosion.fs", GL_FRAGMENT_SHADER)}, "Shader_Mesh3d#Random");
        #endif

        chestTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/chestUV.png", "uvMap:Chest");
        skeletonTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/skeletonUV.png", "uvMap:Skeleton");
        demonTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/demonUV.png", "uvMap:Demon");
        mechTexture = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/mechUV.png", "uvMap:Mech");
        backgroundTexture = resourceManager->loadResource<chaos::Texture>("files/textures/brick.jpg", "background");
        bitmapFont = resourceManager->getResource<chaos::BitmapFont>("Calibri");

        actModel = new chaos::Model(renderer, chestPrefab);
        actTexture = resourceManager->getResource<chaos::Texture>("uvMap:Chest");
        loadModel(0);
        cam = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        cam->moveZ(21.f);
        cam->moveY(3.5f);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        textLeft = new chaos::BitmapFontSprite(renderer, bitmapFont,    "press [key] to change shader\n"
                                                                        "[shift+e] -> \"explosion\"\n"
                                                                        "[shift+v] -> normal vectors visualizer\n"
                                                                        "[shift+n] -> standard display\n"
                                                                        "[shift+r] -> randomization on Y axis\n"
                                                                        "[z] -> previous model\n"
                                                                        "[x] -> next model");
        textLeft->setFitToScreen(true);
        textLeft->moveY(2.0-64.f/window->getStyle().height);

        textRight = new chaos::BitmapFontSprite(renderer, bitmapFont,   "source code:\n"
                                                                        "https://github.com/stawrocek/chaos_engine\n");
        textRight->setFitToScreen(true);
        textRight->moveY(64.f/window->getStyle().height);

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
            if(renderMode == 3){
                GLfloat currTime = window->getRunningTimeAsSeconds();
                actModel->setShader("Shader_Mesh3d#Random");
                actModel->getShader()->run();
                actModel->getShader()->setUniform("time", currTime);
                actTexture->bind();
                actModel->draw();
            }


            textLeft->draw();
            textRight->draw();
        }
    }
    virtual void deliverEvent(void* event){
        chaos::Event* e = (chaos::Event*)event;
        if(e->key.keysym.sym == SDLK_n && (e->key.keysym.mod & KMOD_SHIFT)){
            renderMode=0;
        }
        if(e->key.keysym.sym == SDLK_e && (e->key.keysym.mod & KMOD_SHIFT)){
            renderMode=1;
        }
        if(e->key.keysym.sym == SDLK_v && (e->key.keysym.mod & KMOD_SHIFT)){
            renderMode=2;
        }
        if(e->key.keysym.sym == SDLK_r && (e->key.keysym.mod & KMOD_SHIFT)){
            renderMode=3;
        }
        /*if(e.key.keysym.sym == SDLK_g && (e.key.keysym.mod & KMOD_SHIFT)){
            launchGithub();
        }*/
        if(e->key.keysym.sym == SDLK_z){
            loadModel(-1);
        }
        if(e->key.keysym.sym == SDLK_x){
            loadModel(+1);
        }

        if(e->type == SDL_MOUSEMOTION) {
            cam->processMouse(e->motion.xrel, -e->motion.yrel);
        }
    }

    void loadModel(GLint delta){
        modelCtr += delta;
        if(modelCtr < 0)modelCtr = 3;
        if(modelCtr > 3)modelCtr = 0;
        if(modelCtr == 0){
            actTexture = chestTexture;
            actModel->setMesh(chestPrefab);
            actModel->setScale(0.4f, 0.4f, 0.4f);
            actModel->setY(0.f);
            actModel->setColor(1.f, 1.f, 1.f, 1.f);
        }
        if(modelCtr == 1){
            actTexture = skeletonTexture;
            actModel->setMesh(skeletonPrefab);
            actModel->setScale(.12f, .12f, .12f);
            actModel->setY(0.f);
            actModel->setColor(1.f, 1.f, 1.f, 0.5f);
        }
        if(modelCtr == 2){
            actTexture = demonTexture;
            actModel->setMesh(demonPrefab);
            actModel->setScale(2.5f, 2.5f, 2.5f);
            actModel->setY(0.f);
            actModel->setColor(1.f, 1.f, 1.f, 1.f);
        }
        if(modelCtr == 3){
            actTexture = mechTexture;
            actModel->setMesh(mechPrefab);
            actModel->setScale(0.5f, 0.5f, 0.5f);
            actModel->setY(0.f);
            actModel->setColor(1.f, 1.f, 1.f, 1.f);
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
    chaos::Texture* skeletonTexture;
    chaos::Texture* demonTexture;
    chaos::Texture* mechTexture;
    chaos::MeshPrefab* chestPrefab;
    chaos::MeshPrefab* skeletonPrefab;
    chaos::MeshPrefab* demonPrefab;
    chaos::MeshPrefab* mechPrefab;
    chaos::BitmapFont* bitmapFont;

    chaos::Camera* cam;
    GLuint renderMode = 0; //0->normal, 1->explosion shader, 2->normals shader
    GLfloat moveSpeed=10.f;
    GLint modelCtr=0;
};

#endif // OBJ_VIEWER_HPP


