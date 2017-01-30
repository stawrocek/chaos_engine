#define CHAOS_PLATFORM_PC
//#define CHAOS_PLATFORM_ANDROID

#include <iostream>

#include "../lib-loaders/chaos-sdl2.hpp"
#include "../include/Application.hpp"
#include "../include/InputHandler.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Shader.hpp"
#include "../include/VertexArray.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Transform.hpp"
static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

#include "../examples/basic/basic_app.hpp"

#ifndef ANDROID
int main(int argc, char* argv[]){
    chaos::WindowStyle style("chaos::engine demo", 50, 50, 1024, 600);
    chaos::SDL2Window window(style, SDL_WINDOW_OPENGL);
    BasicApplication* app = new BasicApplication(&window);
    window.runApplication(app);
    delete app;
    return 0;
}
#endif

