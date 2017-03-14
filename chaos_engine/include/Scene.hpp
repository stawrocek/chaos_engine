#ifndef SCENE_HPP
#define SCENE_HPP

#include "Export.hpp"

#include <string>

#include "Renderer.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"

namespace chaos{

class SceneManager;

class CHAOS_EXPORT Scene{
public:
    Scene(std::string _name)
    :name(_name)
    {}

    virtual ~Scene(){}


    virtual void onSceneLoadToMemory(){};
    virtual void onSceneActivate(){};// = 0;
    virtual void update(GLfloat deltaTime){};// = 0;
    virtual void draw(GLfloat deltaTime){};// = 0;
    virtual void deliverEvent(void* e){};// = 0;
    virtual void onSceneDeactivate(){};// = 0;

    std::string getName(){
        return name;
    }

    void setSceneManager(SceneManager* mgr){
        scnManager = mgr;
    }

    void setRenderer(Renderer* ren){
        renderer = ren;
        window = renderer->getTargetWindow();
    }

    void setResourceManager(ResourceManager* mgr){
        resourceManager = mgr;
    }

    void clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

protected:
    std::string name;
    SceneManager* scnManager=nullptr;
    Renderer* renderer;
    ResourceManager* resourceManager;
    Window* window;
};

}

#endif // SCENE_HPP
