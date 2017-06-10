#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

#include "Export.hpp"

#include "Timer.hpp"
#include "InputManager.hpp"

namespace chaos{

class SceneManager;
class Application;

struct CHAOS_EXPORT WindowStyle{
    WindowStyle();
    std::string name;
    GLuint posX;
    GLuint posY;
    GLuint width;
    GLuint height;
    WindowStyle(std::string _name, GLuint _posX, GLuint _posY, GLuint _width, GLuint _height);
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
    virtual GLint getGLDrawableWidth() = 0;
    virtual GLint getHeight() = 0;
    virtual GLint getGLDrawableHeight() = 0;
    virtual GLint getPosX() = 0;
    virtual GLint getPosY() = 0;
    virtual void setRelativeMode(GLboolean mode)=0;
    void setDepthEnabled(GLboolean);
    GLboolean isDepthEnabled();
    void setBlendingEnabled(GLboolean);
    GLboolean isBlendingEnabled();
    GLfloat getDeltaTime();
    GLuint getFPS();
    GLfloat getRunningTime();
    GLfloat getRunningTimeAsSeconds();
    WindowStyle getStyle();
    void setStyle(WindowStyle ws);

    virtual GLvoid* getWindowW32Handle() = 0;

    //input
    virtual void runEvents(SceneManager* sceneManager)=0;
    //virtual void runImmediateGUI();
    GLboolean isTouched(TouchEvent::ButtonCode btn=TouchEvent::ButtonLeft);
    GLboolean isKeyDown(GLuint k);
    virtual GLboolean isFocused()=0;
    virtual GLvoid showCursor(GLboolean flag)=0;
    virtual const GLchar* getClipboardText(void*)=0;
    virtual void setClipboardText(void*, const char* text)=0;
    InputManager* inputManager;

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
