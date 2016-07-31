#include <iostream>

#include "include/Window.hpp"

int main(int argc, char* argv[]){
    std::cout << "BigCalm\n";

    chaos::WindowStyle style("Test 1", 100, 100, 600, 480, SDL_WINDOW_OPENGL);
    chaos::Window window(style);

    GLboolean mainLoop=true;
    while (mainLoop){
	    window.clearColor(0.0, 0.4, 0.0, 1.0);
		SDL_Event event;
		while (SDL_PollEvent(&event)){
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
