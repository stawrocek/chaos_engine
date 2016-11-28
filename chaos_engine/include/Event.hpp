#ifndef EVENT_HPP
#define EVENT_HPP

#include "Export.hpp"
#include <SDL/SDL.h>

namespace chaos{

struct CHAOS_EXPORT Event {
    //union copied from sdl 2.0.4 source
    union {
        Uint32 type;                    /**< Event type, shared with all events */
        SDL_CommonEvent common;         /**< Common event data */
        SDL_WindowEvent window;         /**< Window event data */
        SDL_KeyboardEvent key;          /**< Keyboard event data */
        SDL_TextEditingEvent edit;      /**< Text editing event data */
        SDL_TextInputEvent text;        /**< Text input event data */
        SDL_MouseMotionEvent motion;    /**< Mouse motion event data */
        SDL_MouseButtonEvent button;    /**< Mouse button event data */
        SDL_MouseWheelEvent wheel;      /**< Mouse wheel event data */
        SDL_JoyAxisEvent jaxis;         /**< Joystick axis event data */
        SDL_JoyBallEvent jball;         /**< Joystick ball event data */
        SDL_JoyHatEvent jhat;           /**< Joystick hat event data */
        SDL_JoyButtonEvent jbutton;     /**< Joystick button event data */
        SDL_JoyDeviceEvent jdevice;     /**< Joystick device change event data */
        SDL_ControllerAxisEvent caxis;      /**< Game Controller axis event data */
        SDL_ControllerButtonEvent cbutton;  /**< Game Controller button event data */
        SDL_ControllerDeviceEvent cdevice;  /**< Game Controller device event data */
        SDL_AudioDeviceEvent adevice;
        SDL_QuitEvent quit;             /**< Quit request event data */
        SDL_UserEvent user;             /**< Custom event data */
        SDL_SysWMEvent syswm;           /**< System dependent window event data */
        SDL_TouchFingerEvent tfinger;   /**< Touch finger event data */
        SDL_MultiGestureEvent mgesture; /**< Gesture event data */
        SDL_DollarGestureEvent dgesture; /**< Gesture event data */
        SDL_DropEvent drop;             /**< Drag and drop event data */


        /* This is necessary for ABI compatibility between Visual C++ and GCC
           Visual C++ will respect the push pack pragma and use 52 bytes for
           this structure, and GCC will use the alignment of the largest datatype
           within the union, which is 8 bytes.
           So... we'll add padding to force the size to be 56 bytes for both.
        */
        //Uint8 padding[56];
    };

    int getChar() {
        return key.keysym.sym;
    };

    int getMouseButton() {
        return button.button;
    }

    void initFromSDL_Event(SDL_Event* e) {
        type = e->type;
        if(e->type == SDL_AUDIODEVICEADDED || e->type == SDL_AUDIODEVICEREMOVED)
            adevice = e->adevice;
        else if(e->type == SDL_CONTROLLERAXISMOTION)
            caxis = e->caxis;
        else if(e->type == SDL_CONTROLLERBUTTONDOWN || e->type == SDL_CONTROLLERBUTTONUP)
            cbutton = e->cbutton;
        else if(e->type == SDL_CONTROLLERDEVICEADDED || e->type == SDL_CONTROLLERDEVICEREMOVED || e->type == SDL_CONTROLLERDEVICEREMAPPED)
            cdevice = e->cdevice;
        else if(e->type == SDL_DOLLARGESTURE || e->type == SDL_DOLLARRECORD)
            dgesture = e->dgesture;
        else if(e->type == SDL_DROPFILE)
            drop = e->drop;
        else if(e->type == SDL_FINGERMOTION || e->type == SDL_FINGERDOWN || e->type == SDL_FINGERUP)
            tfinger = e->tfinger;
        else if(e->type == SDL_KEYDOWN || e->type == SDL_KEYUP)
            key = e->key;
        else if(e->type == SDL_JOYAXISMOTION)
            jaxis = e->jaxis;
        else if(e->type == SDL_JOYBALLMOTION)
            jball = e->jball;
        else if(e->type == SDL_JOYHATMOTION)
            jhat = e->jhat;
        else if(e->type == SDL_JOYBUTTONDOWN || e->type == SDL_JOYBUTTONUP)
            jbutton = e->jbutton;
        else if(e->type == SDL_JOYDEVICEADDED || e->type == SDL_JOYDEVICEREMOVED)
            jdevice = e->jdevice;
        else if(e->type == SDL_MOUSEMOTION)
            motion = e->motion;
        else if(e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
            button = e->button;
        else if(e->type == SDL_MOUSEWHEEL)
            wheel = e->wheel;
        else if(e->type == SDL_MULTIGESTURE)
            mgesture = e->mgesture;
        else if(e->type == SDL_QUIT)
            quit = e->quit;
        else if(e->type == SDL_SYSWMEVENT)
            syswm = e->syswm;
        else if(e->type == SDL_TEXTEDITING)
            edit = e->edit;
        else if(e->type == SDL_TEXTINPUT)
            text = e->text;
        else if(e->type == SDL_USEREVENT)
            user = e->user;
        else if(e->type == SDL_WINDOWEVENT)
            window = e->window;
    }
};

}

#endif //EVENT_HPP
