#ifndef CHAOS_SDL2_HPP
#define CHAOS_SDL2_HPP

#include "../include/Window.hpp"
#include "../include/SceneManager.hpp"

#include <SDL2/SDL.h>

namespace chaos{

class SDL2Window: public Window{
public:
    SDL2Window(WindowStyle style, SDL_WindowFlags _flags)
    :Window(style), flags(_flags)
    {
        window = SDL_CreateWindow(style.name.c_str(), style.posX, style.posY, style.width, style.height, flags);
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

    virtual ~SDL2Window(){
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Window* getWindowHandle()       {return window;}
    SDL_GLContext* getGLContextHandle() {return &context;}

    void swapBuffers(){
        SDL_GL_SwapWindow(window);
    }
    void update(){
        deltaTimer.restart();
        if(fpsTimer.getTime() >= 1000){
            fpsVal = fpsCtr;
            fpsCtr=0;
            fpsTimer.restart();
        }
        fpsCtr++;
        swapBuffers();
    }

    GLint getWidth(){
        GLint winWidth, winHeight;
        SDL_GetWindowSize(window, &winWidth, &winHeight);
        return winWidth;
    }

    GLint getHeight(){
        GLint winWidth, winHeight;
        SDL_GetWindowSize(window, &winWidth, &winHeight);
        return winHeight;
    }

    GLint getPosX(){
        GLint posX, posY;
        SDL_GetWindowPosition(window,&posX, &posY);
        return posX;
    }

    GLint getPosY(){
        GLint posX, posY;
        SDL_GetWindowPosition(window,&posX, &posY);
        return posY;
    }

protected:
    SDL_Window* window = nullptr;
    SDL_GLContext context;
    SDL_WindowFlags flags;
};

class SDL2InputManager: public InputManager{
public:
    void runEvents(SceneManager* sceneManager){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            if(sceneManager != nullptr){
                sceneManager->deliverEvent(&event);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT)
                    mTouchDown[MouseButton::BTN_LEFT]=true;
                if(event.button.button == SDL_BUTTON_MIDDLE)
                    mTouchDown[MouseButton::BTN_MIDDLE]=true;
                if(event.button.button == SDL_BUTTON_RIGHT)
                    mTouchDown[MouseButton::BTN_RIGHT]=true;

            }
            else if(event.type == SDL_MOUSEBUTTONUP){
                if(event.button.button == SDL_BUTTON_LEFT)
                    mTouchDown[MouseButton::BTN_LEFT]=false;
                if(event.button.button == SDL_BUTTON_MIDDLE)
                    mTouchDown[MouseButton::BTN_MIDDLE]=false;
                if(event.button.button == SDL_BUTTON_RIGHT)
                    mTouchDown[MouseButton::BTN_RIGHT]=false;
            }
            else if (event.type == SDL_KEYDOWN){
                mKeyDown[event.key.keysym.sym]=true;
            }
            else if (event.type == SDL_KEYUP){
                mKeyDown[event.key.keysym.sym]=false;
            }
        }
    }

    GLuint getMouseX(){
        GLint tmpX,tmpY;
        SDL_GetMouseState(&tmpX,&tmpY);
        return tmpX;
    }

    GLuint getMouseY(){
        GLint tmpX,tmpY;
        SDL_GetMouseState(&tmpX,&tmpY);
        return tmpY;
    }
};


}

#endif // CHAOS_SDL2_HPP

