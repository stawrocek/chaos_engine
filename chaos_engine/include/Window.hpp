#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Export.hpp"

#include <string>
#include <iostream>

#include "Timer.hpp"
#include "Application.hpp"

namespace chaos{

struct CHAOS_EXPORT WindowStyle{
    WindowStyle(){}
    std::string name;
    GLuint posX;
    GLuint posY;
    GLuint width;
    GLuint height;
    WindowStyle(std::string _name, GLuint _posX, GLuint _posY, GLuint _width, GLuint _height)
    :name(_name), posX(_posX), posY(_posY), width(_width), height(_height)
    {}
};

class CHAOS_EXPORT Window
{
public:
    Window(WindowStyle);
    virtual ~Window();
    void runApplication(Application*);
    virtual void clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    virtual void update() = 0;
    virtual void swapBuffers() = 0;
    virtual GLint getWidth() = 0;
    virtual GLint getHeight() = 0;
    virtual GLint getPosX() = 0;
    virtual GLint getPosY() = 0;
    void setDepthEnabled(GLboolean);
    GLboolean isDepthEnabled()          {return depthEnabled;}
    void setBlendingEnabled(GLboolean);
    GLboolean isBlendingEnabled()       {return blendingEnabled;}
    GLfloat getDeltaTime();
    GLuint getFPS();
    GLfloat getRunningTime()            {return totalTimer.getTime();}
    GLfloat getRunningTimeAsSeconds()   {return totalTimer.getTimeAsSeconds();}
    WindowStyle getStyle()              {return winStyle;}

protected:
    GLboolean depthEnabled = true;
    GLboolean blendingEnabled = true;
    Timer deltaTimer;

    Timer fpsTimer;
    Timer totalTimer;

    GLuint fpsCtr=0;
    GLuint fpsVal=0;

    WindowStyle winStyle;
    Application* application;
};

}
#endif // WINDOW_HPP
