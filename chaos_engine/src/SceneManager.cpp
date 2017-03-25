#include "../include/SceneManager.hpp"

#include "../include/ResourceManager.hpp"
#include "../include/Scene.hpp"
#include "../include/Renderer.hpp"

chaos::SceneManager::SceneManager(ResourceManager* rsc, Renderer* ren){
    resourceManager = rsc;
    renderer = ren;
}
chaos::SceneManager::~SceneManager(){
    auto itr = scenes.begin();
    while (itr != scenes.end()) {
        delete itr->second;
        itr = scenes.erase(itr);
    }
}

void chaos::SceneManager::unregisterScene(std::string nameId){
    if(scenes.find(nameId) != scenes.end()){
        delete scenes[nameId];
        scenes.erase(nameId);
    }
}
void chaos::SceneManager::setActiveScene(std::string nameId){
    if(actScene != nullptr){
        actScene->onSceneDeactivate();
    }
    actScene = scenes[nameId];
    renderer->setLightCastersVector(actScene->getLightCastersVector());
    actScene->onSceneActivate();
}
std::string chaos::SceneManager::getActiveSceneName(){
    return actScene->getName();
}
void chaos::SceneManager::deliverEvent(chaos::Event* e){
    actScene->deliverEvent(e);
}
void chaos::SceneManager::runSceneFrame(GLfloat delta){
    actScene->update(delta);
    actScene->draw(delta);
}
