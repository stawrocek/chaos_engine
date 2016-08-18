#include <iostream>

#include "../include/Window.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Transform.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Texture.hpp"
#include "../include/VertexArray.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/Camera.hpp"
#include "../include/Renderer.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    chaos::WindowStyle style("Test 1", 100, 100, 600, 480, SDL_WINDOW_OPENGL);
    chaos::Window window(style);
    chaos::ResourceManager rscManager;
    chaos::Renderer renderer;
    chaos::Texture* texture1 = rscManager.loadResource<chaos::Texture>("files/textures/composition-a-1923-piet-mondrian.jpg", "piet");
    chaos::Texture* texture2 = rscManager.loadResource<chaos::Texture>("files/textures/2001.png", "2001");

    chaos::GameObject testTransform;
    testTransform.setScale(0.5f, 0.5f, 0.5f);
    chaos::GameObject testTransform2;
    testTransform2.setScale(0.5f, 0.5f, 0.5f);
    testTransform2.translate(0.5, 0.5, 0.5);

    chaos::Camera cam;
    cam.moveZ(5.f);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    glm::mat4 mxProj = glm::perspective(glm::radians(45.0f), (GLfloat)style.width/style.height, 0.1f, 100.0f);

    std::vector<GLfloat> vertices = {
        -1.f, -1.f, 0.f, 0.f, 0.f,
        1.f, -1.f, 0.f,  1.f, 0.f,
        -1.f,  1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 0.f,   1.f, 1.f,
        1.f, -1.f, 0.f,  1.f, 0.f,
        -1.f,  1.f, 0.f, 0.f, 1.f
    };

    GLfloat uvVerts[] = {
        0.f, 0.f,
        1.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 1.f
    };

    renderer.addShader({std::make_pair("files/shaders/shader1.vs", GL_VERTEX_SHADER),
                                       std::make_pair("files/shaders/shader1.fs", GL_FRAGMENT_SHADER)}, "testShader");

    renderer.addVAO(3, 0, 2, 0, &vertices, "testVAO");

    GLboolean mainLoop=true;
    GLfloat r=0.0;

    while (mainLoop){
	    window.clearColor(r, 0, 0.0, 1.0);
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

			if(event.type == SDL_MOUSEMOTION) {
                cam.processMouse(event.motion.xrel, -event.motion.yrel);
            }
		}

		if(inputHandler.isKeyDown('r')){
            if(r+0.0001 <= 1.0)
            r+=0.0001;
		}
		if(inputHandler.isKeyDown('e')){
		    if(r-0.0001 >= 0.0)
            r-=0.0001;
		}
		GLfloat deltaTime = window.getDeltaTime();

        if(inputHandler.isKeyDown('a'))
            testTransform.moveX(-1.f * deltaTime);
        if(inputHandler.isKeyDown('d'))
            testTransform.moveX(+1.f * deltaTime);
        if(inputHandler.isKeyDown('w'))
            testTransform.moveY(+1.f * deltaTime);
        if(inputHandler.isKeyDown('s'))
            testTransform.moveY(-1.f * deltaTime);

        if(inputHandler.isKeyDown('h'))
            cam.processKeyboard(chaos::LEFT, deltaTime);
        if(inputHandler.isKeyDown('k'))
            cam.processKeyboard(chaos::RIGHT, deltaTime);
        if(inputHandler.isKeyDown('u'))
            cam.processKeyboard(chaos::FORWARD, deltaTime);
        if(inputHandler.isKeyDown('j'))
            cam.processKeyboard(chaos::BACKWARD, deltaTime);

        renderer.getShader("testShader")->run();

        GLfloat greenValue = 0.5;
        texture1->use(GL_TEXTURE1);

        renderer.getShader("testShader")->setUniform("ourColor", glm::vec4(0.0, r, 0.0, 1.0));
        renderer.getShader("testShader")->setUniform("mx",mxProj*cam.getViewMatrix()*testTransform.getGlobalTransformMatrix());
        renderer.getShader("testShader")->setUniform("tex0", texture1->getId());

        renderer.getVAO("testVAO")->bind();
        glDrawArrays(GL_TRIANGLES, 0, renderer.getVAO("testVAO")->countVertices());
        renderer.getVAO("testVAO")->unbind();

        renderer.getShader("testShader")->setUniform("mx",mxProj*cam.getViewMatrix()* testTransform2.getGlobalTransformMatrix());
        texture2->use(GL_TEXTURE2);
        renderer.getShader("testShader")->setUniform("tex0", texture2->getId());

        renderer.getVAO("testVAO")->bind();
        glDrawArrays(GL_TRIANGLES, 0, renderer.getVAO("testVAO")->countVertices());
        renderer.getVAO("testVAO")->unbind();

        window.update();
    }
}
