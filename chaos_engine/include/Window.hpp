#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL/SDL.h>
#include <string>
#include <iostream>

#include "Export.hpp"

#include "Timer.hpp"

namespace chaos{

struct CHAOS_EXPORT WindowStyle{
    WindowStyle(){}
    std::string name;
    GLuint posX;
    GLuint posY;
    GLuint width;
    GLuint height;
    SDL_WindowFlags flags;
    WindowStyle(std::string _name, GLuint _posX, GLuint _posY, GLuint _width, GLuint _height, SDL_WindowFlags _flags)
    :name(_name), posX(_posX), posY(_posY), width(_width), height(_height), flags(_flags)
    {}
};

class CHAOS_EXPORT Window
{
public:
    Window(WindowStyle);
    virtual ~Window();
    void initOpenGL();
    void clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void update();
    SDL_Window* getWindowHandle()       {return window;}
    SDL_GLContext* getGLContextHandle() {return &context;}
    void setDepthEnabled(GLboolean);
    GLboolean isDepthEnabled()          {return depthEnabled;}
    void setBlendingEnabled(GLboolean);
    GLboolean isBlendingEnabled()       {return blendingEnabled;}
    GLfloat getDeltaTime();
    GLuint getFPS();
    GLfloat getRunningTime()            {return totalTimer.getTime();}
    GLfloat getRunningTimeAsSeconds()   {return totalTimer.getTimeAsSeconds();}
    WindowStyle getStyle()              {return winStyle;}
private:
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    GLboolean depthEnabled = true;
    GLboolean blendingEnabled = true;
    Timer deltaTimer;

    Timer fpsTimer;
    Timer totalTimer;

    GLuint fpsCtr=0;
    GLuint fpsVal=0;

    WindowStyle winStyle;
};

}
#endif // WINDOW_HPP
