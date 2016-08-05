#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>

namespace chaos{

class SceneManager;

class Scene{
public:
    Scene(std::string _name)
    :name(_name)
    {}

    virtual ~Scene(){}

    virtual void onSceneActivate() = 0;
    virtual void update(GLfloat deltaTime) = 0;
    virtual void draw(GLfloat deltaTime) = 0;
    virtual void deliverEvent(chaos::Event&) = 0;
    virtual void onSceneDeactivate() = 0;

    std::string getName(){
        return name;
    }

    void setSceneManager(SceneManager* mgr){
        scnManager = mgr;
    }

    void clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

protected:
    std::string name;
    SceneManager* scnManager=nullptr;
};

}

#endif // SCENE_HPP
