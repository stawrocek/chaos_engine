#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Export.hpp"

#include <string>
#include "Scene.hpp"

namespace chaos{

class CHAOS_EXPORT SceneManager{
public:
    SceneManager(ResourceManager* rsc, Renderer* ren, InputHandler* ipth){
        resourceManager = rsc;
        renderer = ren;
        inputHandler = ipth;
    }
    virtual ~SceneManager(){
        std::cout << "Destructor of SceneManager{\n";
        std::cout << scenes.size() << "\n";
        auto itr = scenes.begin();
        while (itr != scenes.end()) {
            delete itr->second;
            itr = scenes.erase(itr);
        }
        std::cout << scenes.size() << "\n";
        std::cout << "}\n";
    }
    template<typename T>
    void registerScene(std::string name){
        scenes[name] = new T(name);
        scenes[name]->setSceneManager(this);
        scenes[name]->setRenderer(renderer);
        scenes[name]->setResourceManager(resourceManager);
        scenes[name]->setInputHandler(inputHandler);
        scenes[name]->onSceneLoadToMemory();
    }
    void unregisterScene(std::string nameId){
        if(scenes.find(nameId) != scenes.end()){
            delete scenes[nameId];
            scenes.erase(nameId);
        }
    }
    void setActiveScene(std::string nameId){
        if(actScene != nullptr){
            actScene->onSceneDeactivate();
        }
        actScene = scenes[nameId];
        actScene->onSceneActivate();
    }
    std::string getActiveSceneName(){
        return actScene->getName();
    }
    void deliverEvent(chaos::Event& e){
        actScene->deliverEvent(e);
    }
    void runSceneFrame(GLfloat delta){
        actScene->update(delta);
        actScene->draw(delta);
    }

private:
    std::unordered_map<std::string, Scene*> scenes;
    Scene* actScene= nullptr;
    Renderer* renderer;
    ResourceManager* resourceManager;
    InputHandler* inputHandler;
};

}

#endif // SCENEMANAGER_HPP
