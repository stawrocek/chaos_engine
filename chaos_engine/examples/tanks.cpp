#include "../include/Window.hpp"
#include "../include/InputHandler.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Renderer.hpp"
#include "../include/Texture.hpp"
#include "../include/Sprite.hpp"
#include "../include/Camera.hpp"

#include "../tanx/Tank.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    chaos::WindowStyle style("tanx", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    chaos::Window window(style);

    chaos::ResourceManager rscManager;
    chaos::Renderer renderer(&window);

    chaos::Texture* texBackground = rscManager.loadResource<chaos::Texture>("files/textures/composition-a-1923-piet-mondrian.jpg", "piet");

    chaos::Camera cam(&renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)style.width/style.height, 0.1f, 100.0f));
    cam.moveZ(5.f);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    chaos::Sprite spBackground(&renderer, texBackground);
    spBackground.rotateX(3.1415/2.f);
    spBackground.moveY(-0.01f);
    tanx::Tank tank1(&renderer);

    bool mainLoop = true;
    while (mainLoop){
	    window.clearColor(0.4, 0.2, 0.2, 1.0);
	    GLfloat deltaTime = window.getDeltaTime();
	    renderer.setCamCombined(cam.getProjectionMatrix()*cam.getViewMatrix());
	    chaos::Event event;
		while (inputHandler.pollEvent(&event)){
            if (event.type == SDL_QUIT)
				mainLoop = false;

			if (event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    mainLoop = false;
			}
			if(event.type == SDL_MOUSEMOTION) {
                cam.processMouse(event.motion.xrel, -event.motion.yrel);
            }
		}

        if(inputHandler.isKeyDown('a'))cam.processKeyboard(chaos::LEFT, deltaTime);
        if(inputHandler.isKeyDown('d'))cam.processKeyboard(chaos::RIGHT, deltaTime);
        if(inputHandler.isKeyDown('w'))cam.processKeyboard(chaos::FORWARD, deltaTime);
        if(inputHandler.isKeyDown('s'))cam.processKeyboard(chaos::BACKWARD, deltaTime);

		spBackground.draw();
		tank1.draw();
        window.update();
    }
}
