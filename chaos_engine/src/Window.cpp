#include "../include/Window.hpp"

using namespace chaos;

Window::Window(WindowStyle style){
    winStyle = style;
    window = SDL_CreateWindow(style.name.c_str(), style.posX, style.posY, style.width, style.height, style.flags);
    initOpenGL();
    deltaTimer.restart();
    fpsTimer.restart();
    totalTimer.restart();
}

Window::~Window(){
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::initOpenGL(){
    context = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    setDepthEnabled(true);
    setBlendingEnabled(true);

    glewExperimental = GL_TRUE;
    glewInit();

}

void Window::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLfloat Window::getDeltaTime(){
    return deltaTimer.getTimeAsSeconds();
}

void Window::update(){
    deltaTimer.restart();
    if(fpsTimer.getTime() >= 1000){
        fpsVal = fpsCtr;
        fpsCtr=0;
        fpsTimer.restart();
    }
    fpsCtr++;

    SDL_GL_SwapWindow(window);
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
