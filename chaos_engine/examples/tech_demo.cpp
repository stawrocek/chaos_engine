#include <iostream>

#include "../include/Window.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Transform.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Texture.hpp"
#include "../include/VertexArray.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/SceneManager.hpp"

#include "../tech_demo/ObjViewer.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    chaos::WindowStyle style("chaos::engine demo   ~Stanislaw Koza", 50, 50, 1024, 600, SDL_WINDOW_OPENGL);
    chaos::Window window(style);
    glEnable(GL_MULTISAMPLE);
    chaos::Renderer renderer(&window);
    renderer.addShader({ std::make_pair("files/shaders/Model3dExplosion.vs", GL_VERTEX_SHADER),
                    std::make_pair("files/shaders/Model3dRandom.gs", GL_GEOMETRY_SHADER),
                    std::make_pair("files/shaders/Model3dExplosion.fs", GL_FRAGMENT_SHADER)}, "Shader_Mesh3d#Random");
    chaos::ResourceManager rscManager;
    rscManager.loadResource<chaos::BitmapFont>("files/fonts/CalibriBitmap2.fnt", "Calibri");

    chaos::SceneManager scnMgr(&rscManager, &renderer, &inputHandler);
    scnMgr.registerScene<ObjViewer>("ObjViewer");
    scnMgr.setActiveScene("ObjViewer");

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

