#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL/SDL.h>
#include <string>

namespace chaos{

struct WindowStyle{
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

class Window
{
public:
    Window();
    Window(WindowStyle);
    virtual ~Window();
    void initOpenGLGlew();
    void clearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void swapBuffers();
    SDL_Window* getWindowHandle()       {return window;}
    SDL_GLContext* getGLContextHandle() {return &context;}
    void setDepthEnabled(GLboolean);
    GLboolean isDepthEnabled()          {return depthEnabled;}

private:
    SDL_Window* window = nullptr;
    SDL_GLContext context;

    GLboolean depthEnabled = true;
};

}
#endif // WINDOW_HPP
