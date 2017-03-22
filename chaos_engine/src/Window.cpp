#include <iostream>

#include "../include/Window.hpp"
#include "../include/Application.hpp"

chaos::WindowStyle::WindowStyle(){}

chaos::WindowStyle::WindowStyle(std::string _name, GLuint _posX, GLuint _posY, GLuint _width, GLuint _height)
:name(_name), posX(_posX), posY(_posY), width(_width), height(_height)
{}

chaos::Window::Window(){}

chaos::Window::Window(WindowStyle style){
    winStyle = style;
    deltaTimer.restart();
    fpsTimer.restart();
    totalTimer.restart();
}

chaos::Window::~Window(){

}

void chaos::Window::setStyle(WindowStyle ws){
    winStyle=ws;
}

void chaos::Window::runApplication(Application* app){
    application=app;
    app->run();
}

void chaos::Window::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLfloat chaos::Window::getDeltaTime(){
    return deltaTimer.getTimeAsSeconds();
}

GLuint chaos::Window::getFPS(){
    return fpsVal;
}

void chaos::Window::setDepthEnabled(GLboolean b){
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

void chaos::Window::setBlendingEnabled(GLboolean b){
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

GLboolean chaos::Window::isDepthEnabled(){
    return depthEnabled;
}
GLboolean chaos::Window::isBlendingEnabled(){
    return blendingEnabled;
}
GLfloat chaos::Window::getRunningTime(){
    return totalTimer.getTime();
}
GLfloat chaos::Window::getRunningTimeAsSeconds(){
    return totalTimer.getTimeAsSeconds();
}
chaos::WindowStyle chaos::Window::getStyle(){
    return winStyle;
}

void chaos::Window::runEvents(SceneManager* sceneManager){
    inputManager->runEvents(sceneManager);
}
GLboolean chaos::Window::isTouched(TouchEvent::ButtonCode btn){
    return inputManager->isTouched(btn);
}
GLboolean chaos::Window::isKeyDown(GLuint k){
    return inputManager->isKeyDown(k);
}
