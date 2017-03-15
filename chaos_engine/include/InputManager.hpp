#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "Export.hpp"

#include <unordered_map>

namespace chaos{

class SceneManager;

enum MouseButton{
    BTN_LEFT=0,
    BTN_MIDDLE=1,
    BTN_RIGHT=2
};

class CHAOS_EXPORT InputManager{
public:
    virtual void runEvents(SceneManager* sceneManager)=0;
    virtual GLuint getMouseX()=0;
    virtual GLuint getMouseY()=0;

    virtual GLboolean isTouched(MouseButton btn=BTN_LEFT);
    virtual GLboolean isKeyDown(GLuint k);

protected:
    struct ButtonStateFunctor{
        template <typename T> std::size_t operator()(T t) const {
            return static_cast<std::size_t>(t);
        }
    };
    std::unordered_map<MouseButton, GLboolean, ButtonStateFunctor> mTouchDown;
    std::unordered_map<GLuint, GLboolean, ButtonStateFunctor> mKeyDown;
};

}
#endif // INPUT_MANAGER_HPP
