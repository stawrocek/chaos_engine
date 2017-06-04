#ifndef EVENT_HPP
#define EVENT_HPP

namespace chaos{

struct CHAOS_EXPORT KeyboardEvent{
    enum KeyCode{
        Key1='1',
        Key2='2',
        Key3='3',
        Key4='4',
        Key5='5',
        Key6='6',
        Key7='7',
        Key8='8',
        Key9='9',

        KeyA='A',
        KeyB='B',
        KeyC='C',
        KeyD='D',
        KeyE='E',
        KeyF='F',
        KeyG='G',
        KeyH='H',
        KeyI='I',
        KeyJ='J',
        KeyK='K',
        KeyL='L',
        KeyM='M',
        KeyN='N',
        KeyO='O',
        KeyP='P',
        KeyQ='Q',
        KeyR='R',
        KeyS='S',
        KeyT='T',
        KeyU='U',
        KeyV='V',
        KeyW='W',
        KeyX='X',
        KeyY='Y',
        KeyZ='Z',
        Key0='0',

        KeyBackspace=8,
        KeyTab=9,
        KeyEnter=13,
        KeyLeftShift=14,
        KeyRightShift=15,
        KeyLeftControl=16,
        KeyRightControl=17,
        KeyPause=19,
        KeyCapsLock=20,
        KeyEscape=27,
        KeyPageUp=33,
        KeyPageDown=34,
        KeyEnd=35,
        KeyHome=36,
        KeyLeftArrow=37,
        KeyUpArrow=38,
        KeyRightArrow=39,
        KeyDownArrow=40,
        KeyInsert=45,
        KeyDelete=46,
        KeyLeftAlt=91,
        KeyRightAlt=92,
        KeySelect=93,
        KeyNum0=96,
        KeyNum1=97,
        KeyNum2=98,
        KeyNum3=99,
        KeyNum4=100,
        KeyNum5=101,
        KeyNum6=102,
        KeyNum7=103,
        KeyNum8=104,
        KeyNum9=105,
        KeyMultiply=106,
        KeyPlus=107,
        KeyMinus=109,
        KeyDecimalPoint=110,
        KeyNumDivide=111,
        KeyF1=112,
        KeyF2=113,
        KeyF3=114,
        KeyF4=115,
        KeyF5=116,
        KeyF6=117,
        KeyF7=118,
        KeyF8=119,
        KeyF9=120,
        KeyF10=121,
        KeyF11=122,
        KeyF12=123,
        KeyNumLock=144,
        KeyScrollLock=145,
        KeySemiColon=186,
        KeyEquals=187,
        KeyComma=188,
        KeyDash=189,
        KeyPeriod=190,
        KeyForwardSlash=191,
        KeyBackQuote=192,
        KeyLeftBracket=219,
        KeyBackSlash=220,
        KeyRightBraket=221,
        KeySingleQuote=222,
        KeyLeftSuper=223,
        KeyRightSuper=224
    };

    KeyCode keyCode;
};

struct CHAOS_EXPORT TouchEvent{
    enum ButtonCode{
        ButtonLeft=0,
        ButtonMiddle=1,
        ButtonRight=2
    };

    ButtonCode buttonCode;
    GLint posX, posY;
};

struct CHAOS_EXPORT MouseMoveEvent{
    GLint posX, posY, relX, relY;
};

struct CHAOS_EXPORT MouseWheelEvent{
    GLint x, y;
    GLuint direction;
};

struct CHAOS_EXPORT TextInputEvent{
    char text[32];
};

struct CHAOS_EXPORT Event{
    enum EventType{
        None=0,
        KeyDown,
        KeyUp,
        TouchDown,
        TouchUp,
        MouseMotion,
        MouseWheel,
        TextInput
    };

    union{
        KeyboardEvent keyEvent;
        TouchEvent touchEvent;
        MouseMoveEvent motionEvent;
        MouseWheelEvent wheelEvent;
        TextInputEvent textInputEvent;
    };

    EventType type;
    void* origEvent;
};

}

#endif // EVENT_HPP
