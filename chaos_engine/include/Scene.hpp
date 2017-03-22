#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>

#include "Export.hpp"

//could be predefined, but
#include "Window.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"
#include "Event.hpp"
#include "ShaderProgram.hpp"
#include "VertexArray.hpp"

namespace chaos{

class SceneManager;

class CHAOS_EXPORT Scene{
public:
    Scene(std::string _name);
    virtual ~Scene();

    virtual void onSceneLoadToMemory();
    virtual void onSceneActivate();
    virtual void update(GLfloat deltaTime);
    virtual void draw(GLfloat deltaTime);
    virtual void deliverEvent(Event* e);
    virtual void onSceneDeactivate();

    std::string getName();
    void setSceneManager(SceneManager* mgr);
    void setRenderer(Renderer* ren);
    void setResourceManager(ResourceManager* mgr);
    void clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

protected:
    std::string name;
    SceneManager* scnManager=nullptr;
    Renderer* renderer;
    ResourceManager* resourceManager;
    Window* window;
};

}

#endif // SCENE_HPP
