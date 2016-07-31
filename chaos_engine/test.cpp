#include <iostream>

#include "include/Window.hpp"
#include "include/InputHandler.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    std::cout << "BigCalm\n";

    chaos::WindowStyle style("Test 1", 100, 100, 600, 480, SDL_WINDOW_OPENGL);
    chaos::Window window(style);

    GLboolean mainLoop=true;
    while (mainLoop){
	    window.clearColor(0.0, 0.4, 0.0, 1.0);
		chaos::Event event;
		while (inputHandler.pollEvent(&event)){
			if (event.type == SDL_QUIT)
				mainLoop = false;

			if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
				case SDLK_ESCAPE:
					mainLoop = false;
					break;
				}
			}
		}
        window.swapBuffers();
    }
}
