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
class LightCaster;

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
    void addLightCaster(LightCaster* light);
    std::vector<LightCaster*>* getLightCastersVector();

protected:
    std::string name;
    SceneManager* scnManager=nullptr;
    Renderer* renderer=nullptr;
    ResourceManager* resourceManager=nullptr;
    Window* window=nullptr;
    std::vector<LightCaster*> vecLightCasters;
};

}

#endif // SCENE_HPP
