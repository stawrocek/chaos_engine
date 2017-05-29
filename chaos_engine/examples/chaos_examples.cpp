#define CHAOS_PLATFORM_PC

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "../lib-loaders/chaos-sdl2.hpp"
#include "../include/Application.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Shader.hpp"

#include "../include/VertexArray.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Transform.hpp"

#include "app.hpp"

ChaosExampleLibraryApp* app;

void emscriptenLoop(void* ){
    app->onDraw();
}

int main(int argc, char* argv[]){
    chaos::WindowStyle style("chaos::engine demo", 50, 50, 1024, 600);
    chaos::SDL2Window window(style, SDL_WINDOW_OPENGL);
    window.inputManager = new chaos::SDL2InputManager();
    app = new ChaosExampleLibraryApp(&window);
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    chaos::Application::setDataStorageDirectory("assets/");
    app->onCreate();
    emscripten_set_main_loop_arg(emscriptenLoop, NULL, -1, 1);
#else
    window.runApplication(app);
#endif

    delete app;
    return 0;
}


