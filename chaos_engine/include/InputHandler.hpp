#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "Export.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "Event.hpp"

namespace chaos {

class CHAOS_EXPORT InputHandler
{
public:

    static InputHandler& getInstance() {
        static InputHandler handler;
        return handler;
    }

    static bool pollEvent(Event*);
    static bool isKeyDown(int c);
    static bool isMouseButtonDown(int b);
    static double getMouseX();
    static double getMouseY();
    static double getMouseDesktopX();
    static double getMouseDesktopY();

private:
    InputHandler(){};

    static std::map<int, bool> keyboardEventsProxy;
    static std::map<int, bool> mouseEventsProxy;
};

}
#endif // INPUT_HANDLER_HPP
