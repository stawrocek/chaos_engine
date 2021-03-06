#ifndef CHAOS_SDL2_HPP
#define CHAOS_SDL2_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include "../include/Window.hpp"
#include "../include/SceneManager.hpp"
#include "../lib-loaders/ImGUI_Impl_Chaos.hpp"

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

        //setDepthEnabled(true);
        setBlendingEnabled(true);

        GLboolean isInitializationOk = initializeGLEW();
        if(isInitializationOk){
            SHOUT("GLEW initialization ok\n");
        }
        else{
            SHOUT("GLEW initialization error\n");
        }
    }

    virtual ~SDL2Window(){
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        ImGui_ImplChaos_Shutdown();
    }

    SDL_Window* getWindowHandle()       {return window;}
    SDL_GLContext* getGLContextHandle() {return &context;}

    void swapBuffers() override {
        SDL_GL_SwapWindow(window);
    }
    void update() override {
        ImGui::Render();
        deltaTimer.restart();
        if(fpsTimer.getTime() >= 1000){
            fpsVal = fpsCtr;
            fpsCtr=0;
            fpsTimer.restart();
        }
        fpsCtr++;
        swapBuffers();
    }

    GLint getWidth() override {
        GLint winWidth, winHeight;
        SDL_GetWindowSize(window, &winWidth, &winHeight);
        return winWidth;
    }

    GLint getGLDrawableWidth() override {
        GLint winWidth, winHeight;
        SDL_GL_GetDrawableSize(window, &winWidth, &winHeight);
        return winWidth;
    }

    GLint getHeight() override {
        GLint winWidth, winHeight;
        SDL_GetWindowSize(window, &winWidth, &winHeight);
        return winHeight;
    }

    GLint getGLDrawableHeight() override {
        GLint winWidth, winHeight;
        SDL_GL_GetDrawableSize(window, &winWidth, &winHeight);
        return winHeight;
    }

    GLint getPosX() override {
        GLint posX, posY;
        SDL_GetWindowPosition(window,&posX, &posY);
        return posX;
    }

    GLint getPosY() override {
        GLint posX, posY;
        SDL_GetWindowPosition(window,&posX, &posY);
        return posY;
    }

    void setRelativeMode(GLboolean mode) override {
        if(mode == true)
            SDL_SetRelativeMouseMode(SDL_TRUE);
        else
            SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    GLvoid* getWindowW32Handle() override {
        #ifdef WINDOWS
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);
        SDL_GetWindowWMInfo(window, &wmInfo);
        return wmInfo.info.win.window;
        #endif // WINDOWS
        return nullptr;
    }

    GLboolean isFocused() override {
        return (SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS) == SDL_WINDOW_MOUSE_FOCUS;
    }

    GLvoid showCursor(GLboolean flag) override {
        SDL_ShowCursor(flag);
    }

    const GLchar* getClipboardText(void* clipboardPtr) override {
        return SDL_GetClipboardText();
    }
    void setClipboardText(void* clipboardPtr, const char* text) override {
        SDL_SetClipboardText(text);
    }

    void runEvents(chaos::SceneManager* sceneManager) override {
        inputManager->runEvents(sceneManager);
        ImGui_ImplChaos_NewFrame(this);
    }

protected:
    SDL_Window* window = nullptr;
    SDL_GLContext context;
    SDL_WindowFlags flags;
};

class SDL2InputManager: public InputManager{
public:
    SDL2InputManager(){
        for(int i = 0; i <= 9; i++)
            mKeyCodes[SDL_Keycode(SDLK_0+i)]=KeyboardEvent::KeyCode(KeyboardEvent::Key0+i);
        for(int i = 0; i <= 'z'-'a'; i++)
            mKeyCodes[SDL_Keycode(SDLK_a+i)]=KeyboardEvent::KeyCode(KeyboardEvent::KeyA+i);
        for(int i = 0; i <= 12; i++)
            mKeyCodes[SDL_Keycode(SDLK_F1+i)]=KeyboardEvent::KeyCode(KeyboardEvent::KeyF1+i);
        for(int i = 0; i <= 9; i++)
            mKeyCodes[SDL_Keycode(SDLK_KP_0+i)]=KeyboardEvent::KeyCode(KeyboardEvent::KeyNum0+i);

        mKeyCodes[SDLK_BACKSPACE]=KeyboardEvent::KeyBackspace;
        mKeyCodes[SDLK_TAB]=KeyboardEvent::KeyTab;
        mKeyCodes[SDLK_LALT]=KeyboardEvent::KeyLeftAlt;
        mKeyCodes[SDLK_RALT]=KeyboardEvent::KeyRightAlt;
        mKeyCodes[SDLK_RETURN]=KeyboardEvent::KeyEnter;
        mKeyCodes[SDLK_LSHIFT]=KeyboardEvent::KeyLeftShift;
        mKeyCodes[SDLK_RSHIFT]=KeyboardEvent::KeyRightShift;
        mKeyCodes[SDLK_LCTRL]=KeyboardEvent::KeyLeftControl;
        mKeyCodes[SDLK_RCTRL]=KeyboardEvent::KeyRightControl;
        mKeyCodes[SDLK_PAUSE]=KeyboardEvent::KeyPause;
        mKeyCodes[SDLK_CAPSLOCK]=KeyboardEvent::KeyCapsLock;
        mKeyCodes[SDLK_ESCAPE]=KeyboardEvent::KeyEscape;
        mKeyCodes[SDLK_PAGEUP]=KeyboardEvent::KeyPageUp;
        mKeyCodes[SDLK_PAGEDOWN]=KeyboardEvent::KeyPageDown;
        mKeyCodes[SDLK_END]=KeyboardEvent::KeyEnd;
        mKeyCodes[SDLK_HOME]=KeyboardEvent::KeyHome;
        mKeyCodes[SDLK_LEFT]=KeyboardEvent::KeyLeftArrow;
        mKeyCodes[SDLK_UP]=KeyboardEvent::KeyUpArrow;
        mKeyCodes[SDLK_RIGHT]=KeyboardEvent::KeyRightArrow;
        mKeyCodes[SDLK_DOWN]=KeyboardEvent::KeyDownArrow;
        mKeyCodes[SDLK_INSERT]=KeyboardEvent::KeyInsert;
        mKeyCodes[SDLK_DELETE]=KeyboardEvent::KeyDelete;
        mKeyCodes[SDLK_SELECT]=KeyboardEvent::KeySelect;
        mKeyCodes[SDLK_PLUS]=KeyboardEvent::KeyPlus;
        mKeyCodes[SDLK_MINUS]=KeyboardEvent::KeyMinus;
        mKeyCodes[SDLK_DECIMALSEPARATOR]=KeyboardEvent::KeyDecimalPoint;
        mKeyCodes[SDLK_KP_DIVIDE]=KeyboardEvent::KeyNumDivide;
        mKeyCodes[SDLK_NUMLOCKCLEAR]=KeyboardEvent::KeyNumLock;
        mKeyCodes[SDLK_SCROLLLOCK]=KeyboardEvent::KeyScrollLock;
        mKeyCodes[SDLK_SEMICOLON]=KeyboardEvent::KeySemiColon;
        mKeyCodes[SDLK_EQUALS]=KeyboardEvent::KeyEquals;
        mKeyCodes[SDLK_COMMA]=KeyboardEvent::KeyComma;
        //mKeyCodes[SDLK_]=KeyboardEvent::KeyDash;
        mKeyCodes[SDLK_PERIOD]=KeyboardEvent::KeyPeriod;
        mKeyCodes[SDLK_BACKQUOTE]=KeyboardEvent::KeyBackQuote;
        mKeyCodes[SDLK_LEFTBRACKET]=KeyboardEvent::KeyLeftBracket;
        mKeyCodes[SDLK_BACKSLASH]=KeyboardEvent::KeyBackSlash;
        mKeyCodes[SDLK_RIGHTBRACKET]=KeyboardEvent::KeyRightBraket;
        mKeyCodes[SDLK_QUOTE]=KeyboardEvent::KeySingleQuote;
    }

    void runEvents(SceneManager* sceneManager){
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)){
            chaos::Event ev = translateEvent(&sdlEvent);
            ImGui_ImplChaos_ProcessEvent(&ev, this);
            if(sceneManager != nullptr){
                if(ev.type != Event::KeyDown)
                    sceneManager->deliverEvent(&ev);
                else{
                    if(!isKeyDown(ev.keyEvent.keyCode)){
                        sceneManager->deliverEvent(&ev);
                    }
                }
            }
            if (ev.type == Event::TouchDown){
                mTouchDown[ev.touchEvent.buttonCode]=true;
            }
            else if(ev.type == Event::TouchUp){
                mTouchDown[ev.touchEvent.buttonCode]=false;
            }
            else if (ev.type == Event::KeyDown){
                mKeyDown[ev.keyEvent.keyCode]=true;
            }
            else if (ev.type == Event::KeyUp){
                mKeyDown[ev.keyEvent.keyCode]=false;
            }
        }
    }

    chaos::Event translateEvent(void* nativeEvent){
        chaos::Event ev;
        SDL_Event* sdlEv = (SDL_Event*)nativeEvent;
        ev.origEvent = nativeEvent;
        if(sdlEv->type == SDL_MOUSEBUTTONDOWN || sdlEv->type == SDL_MOUSEBUTTONUP){
            ev.type = chaos::Event::TouchDown;
            if(sdlEv->type == SDL_MOUSEBUTTONUP)
                ev.type = chaos::Event::TouchUp;
            ev.touchEvent.posX = sdlEv->button.x;
            ev.touchEvent.posY = sdlEv->button.y;
            if(sdlEv->button.button == SDL_BUTTON_LEFT) ev.touchEvent.buttonCode = chaos::TouchEvent::ButtonLeft;
            if(sdlEv->button.button == SDL_BUTTON_MIDDLE) ev.touchEvent.buttonCode = chaos::TouchEvent::ButtonMiddle;
            if(sdlEv->button.button == SDL_BUTTON_RIGHT) ev.touchEvent.buttonCode = chaos::TouchEvent::ButtonRight;
        }
        else if(sdlEv->type == SDL_KEYDOWN || sdlEv->type == SDL_KEYUP){
            ev.type = chaos::Event::KeyDown;
            if(sdlEv->type == SDL_KEYUP)
                ev.type = chaos::Event::KeyUp;
            ev.keyEvent.keyCode = mKeyCodes[sdlEv->key.keysym.sym];
        }
        else if(sdlEv->type == SDL_TEXTINPUT){
            ev.type = chaos::Event::TextInput;
            strcpy(ev.textInputEvent.text, sdlEv->text.text);
        }
        else if(sdlEv->type == SDL_MOUSEMOTION){
            ev.type = chaos::Event::MouseMotion;
            ev.motionEvent.posX = sdlEv->motion.x;
            ev.motionEvent.posY = sdlEv->motion.y;
            ev.motionEvent.relX = sdlEv->motion.xrel;
            ev.motionEvent.relY = sdlEv->motion.yrel;
        }
        else if(sdlEv->type == SDL_MOUSEWHEEL){
            ev.type = chaos::Event::MouseWheel;
            ev.wheelEvent.x = sdlEv->wheel.x;
            ev.wheelEvent.y = sdlEv->wheel.y;
            ev.wheelEvent.direction = sdlEv->wheel.direction;
        }
        return ev;
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

protected:
    std::unordered_map<SDL_Keycode, chaos::KeyboardEvent::KeyCode> mKeyCodes;
};


}

#endif // CHAOS_SDL2_HPP

