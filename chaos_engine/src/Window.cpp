#include "Window.hpp"

using namespace chaos;

Window::Window(){
    window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_OPENGL);
    initOpenGLGlew();
}

Window::Window(WindowStyle style){
     window = SDL_CreateWindow(style.name.c_str(), style.posX, style.posY, style.width, style.height, style.flags);
     initOpenGLGlew();
}

Window::~Window(){
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::initOpenGLGlew(){
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    setDepthEnabled(true);

    context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    glewInit();
}

void Window::clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers(){
    SDL_GL_SwapWindow(window);
}

void Window::setDepthEnabled(GLboolean b){
    depthEnabled=b;
    if(b){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    else{
        glDisable(GL_DEPTH_TEST);
        glDepthFunc(GL_NEVER);
    }
};
