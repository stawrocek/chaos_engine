#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "Export.hpp"

#include <string>
#include "Scene.hpp"

namespace chaos{

class CHAOS_EXPORT SceneManager{
public:
    SceneManager(ResourceManager* rsc, Renderer* ren){
        resourceManager = rsc;
        renderer = ren;
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
    void deliverEvent(void* e){
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
};

}

#endif // SCENEMANAGER_HPP
