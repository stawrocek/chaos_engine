#include "../include/InputManager.hpp"

GLboolean chaos::InputManager::isTouched(TouchEvent::ButtonCode btn){
    if(mTouchDown.find(btn) == mTouchDown.end())
        return false;
    return mTouchDown[btn];
}

GLboolean chaos::InputManager::isKeyDown(GLuint k){
    if(mKeyDown.find(k) == mKeyDown.end())
        return false;
    return mKeyDown[k];
}

void chaos::InputManager::pushEvent(chaos::Event ev){
    qEvents.push(ev);
}
