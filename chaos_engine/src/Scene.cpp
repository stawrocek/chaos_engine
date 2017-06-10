#include "../include/Scene.hpp"

chaos::Scene::Scene(std::string _name)
:name(_name)
{}

chaos::Scene::~Scene(){}


void chaos::Scene::onSceneLoadToMemory(){};
void chaos::Scene::onSceneActivate(){};
void chaos::Scene::update(GLfloat deltaTime){};
void chaos::Scene::draw(GLfloat deltaTime){};
void chaos::Scene::deliverEvent(Event* e){};
void chaos::Scene::onSceneDeactivate(){};
void chaos::Scene::onGUI(){};

std::string chaos::Scene::getName(){
    return name;
}

void chaos::Scene::setSceneManager(SceneManager* mgr){
    scnManager = mgr;
}

void chaos::Scene::setRenderer(Renderer* ren){
    renderer = ren;
    window = renderer->getTargetWindow();
}

void chaos::Scene::setResourceManager(ResourceManager* mgr){
    resourceManager = mgr;
}

void chaos::Scene::clearWindow(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void chaos::Scene::addLightCaster(chaos::LightCaster* light){
    vecLightCasters.push_back(light);
}

std::vector<chaos::LightCaster*>* chaos::Scene::getLightCastersVector(){
    return &vecLightCasters;
}
