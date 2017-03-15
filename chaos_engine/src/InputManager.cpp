#include "../include/InputManager.hpp"

GLboolean chaos::InputManager::isTouched(MouseButton btn){
    if(mTouchDown.find(btn) == mTouchDown.end())
        return false;
    return mTouchDown[btn];
}

GLboolean chaos::InputManager::isKeyDown(GLuint k){
    if(mKeyDown.find(k) == mKeyDown.end())
        return false;
    return mKeyDown[k];
}
