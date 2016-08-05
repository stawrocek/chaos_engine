#include <iostream>

#include "../../include/Window.hpp"
#include "../../include/InputHandler.hpp"
#include "../../include/Transform.hpp"
#include "../../include/ShaderProgram.hpp"
#include "../../include/Texture.hpp"
#include "../../include/VertexArray.hpp"
#include "../../include/ResourceManager.hpp"
#include "../../include/SceneManager.hpp"
#include "scenes/main_menu.hpp"
#include "scenes/scene2.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    chaos::WindowStyle style("SceneManagement", 300, 100, 600, 480, SDL_WINDOW_OPENGL);
    chaos::Window window(style);
    chaos::SceneManager scnMgr;

    std::cout << "test1\n";

    scnMgr.registerScene<MainMenu>("Main_Menu");
    std::cout << "test2\n";
    scnMgr.registerScene<Scene2>("Scene2");
    std::cout << "test3\n";
    scnMgr.setActiveScene("Main_Menu");

    bool mainLoop = true;
    while (mainLoop){
	    //window.clearColor(0.2, 0.4, 0.6, 1.0);
		chaos::Event event;
		while (inputHandler.pollEvent(&event)){
			if (event.type == SDL_QUIT)
				mainLoop = false;

			else if (event.type == SDL_KEYDOWN){
				switch (event.key.keysym.sym){
				case SDLK_ESCAPE:
					mainLoop = false;
					break;
				}
			}
            else
                scnMgr.deliverEvent(event);

		}

		GLfloat deltaTime = window.getDeltaTime();
		scnMgr.runSceneFrame(deltaTime);
        window.update();
    }
}

