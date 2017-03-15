#include "../include/Window.hpp"

using namespace chaos;

WindowStyle::WindowStyle(){}

WindowStyle::WindowStyle(std::string _name, GLuint _posX, GLuint _posY, GLuint _width, GLuint _height)
:name(_name), posX(_posX), posY(_posY), width(_width), height(_height)
{}

Window::Window(){}

Window::Window(WindowStyle style){
    winStyle = style;
    deltaTimer.restart();
    fpsTimer.restart();
    totalTimer.restart();
}

Window::~Window(){

}

void Window::setStyle(WindowStyle ws){
    winStyle=ws;
}

void Window::runApplication(Application* app){
    application=app;
    app->run();
}

void Window::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLfloat Window::getDeltaTime(){
    return deltaTimer.getTimeAsSeconds();
}

GLuint Window::getFPS(){
    return fpsVal;
}

void Window::setDepthEnabled(GLboolean b){
    depthEnabled=b;
    if(depthEnabled){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    else{
        glDisable(GL_DEPTH_TEST);
        glDepthFunc(GL_NEVER);
    }
};

void Window::setBlendingEnabled(GLboolean b){
    blendingEnabled=b;
    if(blendingEnabled){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else{
        glDisable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
    }
}

GLboolean Window::isDepthEnabled(){
    return depthEnabled;
}
GLboolean Window::isBlendingEnabled(){
    return blendingEnabled;
}
GLfloat Window::getRunningTime(){
    return totalTimer.getTime();
}
GLfloat Window::getRunningTimeAsSeconds(){
    return totalTimer.getTimeAsSeconds();
}
WindowStyle Window::getStyle(){
    return winStyle;
}

void Window::runEvents(SceneManager* sceneManager){
    inputManager->runEvents(sceneManager);
}
GLboolean Window::isTouched(MouseButton btn){
    return inputManager->isTouched(btn);
}
GLboolean Window::isKeyDown(GLuint k){
    return inputManager->isKeyDown(k);
}
