#include "../include/Window.hpp"

using namespace chaos;

Window::Window(WindowStyle style){
    winStyle = style;
    deltaTimer.restart();
    fpsTimer.restart();
    totalTimer.restart();
}

Window::~Window(){

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
