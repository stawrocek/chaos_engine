#include "../include/InputHandler.hpp"

using namespace chaos;

std::map<int, bool> InputHandler::keyboardEventsProxy;
std::map<int, bool> InputHandler::mouseEventsProxy;

bool InputHandler::pollEvent(Event* ev) {
    SDL_Event e;
    if(SDL_PollEvent(&e) == 0)
        return false;
    ev->initFromSDL_Event(&e);
    if(e.type == SDL_KEYDOWN){
        keyboardEventsProxy[ev->getChar()] = true;
    }
    else if(e.type == SDL_KEYUP){
        keyboardEventsProxy[ev->getChar()] = false;
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN){
        mouseEventsProxy[ev->getMouseButton()] = true;
    }
    else if(e.type == SDL_MOUSEBUTTONUP){
        mouseEventsProxy[ev->getMouseButton()] = false;
    }
    return true;
}

bool InputHandler::isKeyDown(int c) {
    return keyboardEventsProxy.find(c) != keyboardEventsProxy.end() &&
    keyboardEventsProxy[c] == true;
}

bool InputHandler::isMouseButtonDown(int b) {
    return mouseEventsProxy.find(b) != mouseEventsProxy.end() &&
    mouseEventsProxy[b] == true;
}

double InputHandler::getMouseX() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return x;
}

double InputHandler::getMouseY() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return y;
}

double InputHandler::getMouseDesktopX() {
    int x, y;
    SDL_GetGlobalMouseState(&x, &y);
    return x;
}

double InputHandler::getMouseDesktopY() {
    int x, y;
    SDL_GetGlobalMouseState(&x, &y);
    return y;
}
