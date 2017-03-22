#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <unordered_map>
#include <queue>

#include "Export.hpp"
#include "Event.hpp"

namespace chaos{

class SceneManager;

class CHAOS_EXPORT InputManager{
public:
    virtual void runEvents(SceneManager* sceneManager)=0;
    virtual GLuint getMouseX()=0;
    virtual GLuint getMouseY()=0;
    virtual Event translateEvent(void*)=0;
    virtual GLboolean isTouched(TouchEvent::ButtonCode btn=chaos::TouchEvent::ButtonLeft);
    virtual GLboolean isKeyDown(GLuint k);
    void pushEvent(chaos::Event ev);

protected:
    struct ButtonStateFunctor{
        template <typename T> std::size_t operator()(T t) const {
            return static_cast<std::size_t>(t);
        }
    };
    std::unordered_map<TouchEvent::ButtonCode, GLboolean, ButtonStateFunctor> mTouchDown;
    std::unordered_map<GLuint, GLboolean, ButtonStateFunctor> mKeyDown;
    std::queue<chaos::Event> qEvents;
};

}
#endif // INPUT_MANAGER_HPP
