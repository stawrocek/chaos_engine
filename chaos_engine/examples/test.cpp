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
#include "../include/Primitives.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    chaos::WindowStyle style("Test 1", 100, 100, 600, 480, SDL_WINDOW_OPENGL);
    chaos::Window window(style);
    chaos::ResourceManager rscManager;
    chaos::Renderer renderer;
    chaos::Texture* texture1 = rscManager.loadResource<chaos::Texture>("files/textures/composition-a-1923-piet-mondrian.jpg", "piet");
    chaos::Texture* texture2 = rscManager.loadResource<chaos::Texture>("files/textures/2001.png", "2001");

    chaos::GameObject testTransform(&renderer);
    testTransform.setScale(0.5f, 0.5f, 0.5f);
    chaos::GameObject testTransform2(&renderer);
    testTransform2.setScale(0.5f, 0.5f, 0.5f);
    testTransform2.translate(0.5f, 0.5f, 0.5f);


    chaos::Rectangle rect1(&renderer);
    rect1.setColor(glm::vec4(0.f, 1.f, 0.f, 1.f));
    rect1.translate(1.f, 0.f, 0.f);

    chaos::Cube cube1(&renderer);
    cube1.setColor(glm::vec4(0.2f, 0.4f, 0.6f, 0.75f));
    cube1.moveY(1.5f);
    cube1.setScale(0.2f, 0.2f, 0.2f);

    chaos::Circle circle1(&renderer);
    circle1.setColor(glm::vec4(0.8, 0.8, 0.8, 1));
    circle1.moveY(1.75);
    circle1.rotateX(3.1415/2.f);
    circle1.setParent(&cube1);

    chaos::Camera cam(&renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)style.width/style.height, 0.1f, 100.0f));
    cam.moveZ(5.f);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    GLboolean mainLoop=true;

    while (mainLoop){
	    window.clearColor(0.4, 0.2, 0.2, 1.0);
	    renderer.setCamCombined(cam.getProjectionMatrix()*cam.getViewMatrix());
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

        rect1.rotateX(sin(window.getDeltaTime()));
        cube1.rotateY(sin(window.getDeltaTime()));


        renderer.getShader("Shader_Pos.Uv")->run();

        GLfloat greenValue = 0.5;
        texture1->use(GL_TEXTURE1);

        renderer.getShader("Shader_Pos.Uv")->setUniform("ourColor", glm::vec4(0.0, 0.0, 0.0, 1.0));
        renderer.getShader("Shader_Pos.Uv")->setUniform("mx",renderer.getCamCombined()*testTransform.getGlobalTransformMatrix());
        renderer.getShader("Shader_Pos.Uv")->setUniform("tex0", texture1->getId());

        renderer.getVAO("Rectangle:Vao_Pos.Uv")->bind();
        glDrawArrays(GL_TRIANGLES, 0, renderer.getVAO("Rectangle:Vao_Pos.Uv")->countVertices());
        renderer.getVAO("Rectangle:Vao_Pos.Uv")->unbind();

        renderer.getShader("Shader_Pos.Uv")->setUniform("ourColor", glm::vec4(0.0, 0.0, 0.0, 1.0));
        renderer.getShader("Shader_Pos.Uv")->setUniform("mx",renderer.getCamCombined()* testTransform2.getGlobalTransformMatrix());
        texture2->use(GL_TEXTURE2);
        renderer.getShader("Shader_Pos.Uv")->setUniform("tex0", texture2->getId());

        renderer.getVAO("Rectangle:Vao_Pos.Uv")->bind();
        glDrawArrays(GL_TRIANGLES, 0, renderer.getVAO("Rectangle:Vao_Pos.Uv")->countVertices());
        renderer.getVAO("Rectangle:Vao_Pos.Uv")->unbind();

        rect1.draw();
        cube1.draw();
        circle1.draw();

        window.update();
    }
}
