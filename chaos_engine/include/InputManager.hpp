#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "Export.hpp"

#include <unordered_map>

namespace chaos{

enum MouseButton{
    LEFT=0,
    MIDDLE=1,
    RIGHT=2
};

struct MouseButtonFunctor{
    template <typename T> std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};


class CHAOS_EXPORT InputManager{
public:

    virtual void runEvents()=0;
    virtual GLuint getMouseX()=0;
    virtual GLuint getMouseY()=0;

    virtual bool isTouched(MouseButton btn=LEFT){
        if(mTouchDown.find(btn) == mTouchDown.end())
            return false;
        return mTouchDown[btn];
    }

protected:
    std::unordered_map<MouseButton, GLboolean, MouseButtonFunctor> mTouchDown;
};

}
#endif // INPUT_MANAGER_HPP
