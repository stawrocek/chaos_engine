#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>
#include "Scene.hpp"

namespace chaos{

class SceneManager{
public:
    SceneManager(){}
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
    void deliverEvent(Event& e){
        actScene->deliverEvent(e);
    }
    void runSceneFrame(GLfloat delta){
        actScene->update(delta);
        actScene->draw(delta);
    }

private:
    std::unordered_map<std::string, Scene*> scenes;
    Scene* actScene= nullptr;
};

}

#endif // SCENEMANAGER_HPP
