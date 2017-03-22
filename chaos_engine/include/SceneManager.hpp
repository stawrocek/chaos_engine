#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>
#include <unordered_map>

#include "Export.hpp"
#include "Scene.hpp"

namespace chaos{

class ResourceManager;
class Renderer;

class CHAOS_EXPORT SceneManager{
public:
    SceneManager(ResourceManager* rsc, Renderer* ren);
    virtual ~SceneManager();
    template<typename T>
    void registerScene(std::string name){
        scenes[name] = new T(name);
        scenes[name]->setSceneManager(this);
        scenes[name]->setRenderer(renderer);
        scenes[name]->setResourceManager(resourceManager);
        scenes[name]->onSceneLoadToMemory();
    }
    void unregisterScene(std::string nameId);
    void setActiveScene(std::string nameId);
    std::string getActiveSceneName();
    void deliverEvent(Event* e);
    void runSceneFrame(GLfloat delta);

private:
    std::unordered_map<std::string, Scene*> scenes;
    Scene* actScene = nullptr;
    Renderer* renderer = nullptr;
    ResourceManager* resourceManager = nullptr;
};

}

#endif // SCENEMANAGER_HPP
