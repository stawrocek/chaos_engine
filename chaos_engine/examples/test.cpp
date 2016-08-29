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
#include "../include/Sprite.hpp"
#include "../include/BitmapFontSprite.hpp"
#include "../include/Model.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    std::cout << "example 1\n";
    chaos::WindowStyle style("Test 1", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    chaos::Window window(style);
    chaos::ResourceManager rscManager;
    chaos::Renderer renderer(&window);
    chaos::Texture* texture1 = rscManager.loadResource<chaos::Texture>("files/textures/composition-a-1923-piet-mondrian.jpg", "piet");
    chaos::Texture* texture2 = rscManager.loadResource<chaos::Texture>("files/textures/2001.png", "2001");
    chaos::Texture* uvCube = rscManager.loadResource<chaos::Texture>("files/textures/uv_maps/cubeUV.png", "uvMap:Cube");
    chaos::Texture* uvSword = rscManager.loadResource<chaos::Texture>("files/textures/uv_maps/swordUV.png", "uvMap:Sword");
    chaos::BitmapFont* bmf1 = rscManager.loadResource<chaos::BitmapFont>("files/fonts/CalibriBitmap2.fnt", "Calibri");
    chaos::MeshPrefab* mesh1 = rscManager.loadResource<chaos::MeshPrefab>("files/models3d/cube2.obj", "cube");
    chaos::MeshPrefab* mesh2 = rscManager.loadResource<chaos::MeshPrefab>("files/models3d/sword.obj", "sword");
    renderer.addMeshVAO(mesh1);
    renderer.addMeshVAO(mesh2);

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
    circle1.setColor(glm::vec4(0.8, 0.8, 0.8, 0.25));
    circle1.moveY(1.75);
    circle1.rotateX(3.1415/2.f);
    circle1.setParent(&cube1);

    chaos::Sprite sprite1(&renderer, texture1);
    sprite1.moveY(-2);
    sprite1.scaleUp(0.5, 0.5, 0.5);

    //chaos::BitmapFont bmf1("files/fonts/CalibriBitmap2.fnt");

    chaos::BitmapFontSprite bmf1Sprite(&renderer, bmf1, "Your SPECIAL SECRET KEY:\nhttps://www.youtube.com/watch?v=dQw4w9WgXcQ");
    chaos::BitmapFontSprite bmf2Sprite(&renderer, bmf1);
    bmf2Sprite.setParent(&circle1);
    bmf2Sprite.moveY(0.25);
    bmf2Sprite.setColor(glm::vec4(0.0, 1.0, 0.2, 1.0));
    bmf2Sprite.rotateX(3.1415/2.0+3.1415);
    bmf2Sprite.scaleUp(0.5, 0.5, 0.5);

    chaos::Model model1(&renderer, mesh1);
    model1.setColor(glm::vec4(1.f,0.f,0.f,1.f));
    model1.setScale(0.1f, 0.1f, 0.1f);

    chaos::Model model2(&renderer, mesh2);
    model2.setScale(0.2f, 0.2f, 0.2f);
    model2.moveY(3);
    model2.setShader("Shader_Mesh3d#Explosion");

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
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    mainLoop = false;

                if(event.key.keysym.sym ==  SDLK_c){
                    bmf1Sprite.setFitToScreen(!bmf1Sprite.isFitToScreen());
                    bmf2Sprite.setFitToScreen(!bmf2Sprite.isFitToScreen());
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

        if(inputHandler.isKeyDown('l'))
            bmf1Sprite.moveX(-1.f * deltaTime);
        if(inputHandler.isKeyDown('\''))
            bmf1Sprite.moveX(+1.f * deltaTime);
        if(inputHandler.isKeyDown('p'))
            bmf1Sprite.moveY(+1.f * deltaTime);
        if(inputHandler.isKeyDown(';'))
            bmf1Sprite.moveY(-1.f * deltaTime);

        rect1.rotateX(sin(window.getDeltaTime()));
        cube1.rotateY(sin(window.getDeltaTime()));
        bmf1Sprite.rotateY(sin(window.getDeltaTime()));

        GLfloat greenValue = 0.5;
        texture1->bind();
        renderer.getShader("Shader_Pos.Uv")->run();
        renderer.getShader("Shader_Pos.Uv")->setUniform("ourColor", glm::vec4(0.0, 0.0, 0.0, 1.0));
        renderer.getShader("Shader_Pos.Uv")->setUniform("mx",renderer.getCamCombined()*testTransform.getGlobalTransformMatrix());

        renderer.getVAO("Rectangle:Vao_Pos.Uv")->bind();
        glDrawArrays(GL_TRIANGLES, 0, renderer.getVAO("Rectangle:Vao_Pos.Uv")->countVertices());
        renderer.getVAO("Rectangle:Vao_Pos.Uv")->unbind();

        renderer.getShader("Shader_Pos.Uv")->setUniform("ourColor", glm::vec4(0.0, 0.0, 0.0, 1.0));
        renderer.getShader("Shader_Pos.Uv")->setUniform("mx",renderer.getCamCombined()* testTransform2.getGlobalTransformMatrix());
        texture2->bind();

        renderer.getVAO("Rectangle:Vao_Pos.Uv")->bind();
        glDrawArrays(GL_TRIANGLES, 0, renderer.getVAO("Rectangle:Vao_Pos.Uv")->countVertices());
        renderer.getVAO("Rectangle:Vao_Pos.Uv")->unbind();

        rect1.draw();
        cube1.draw();
        circle1.draw();
        sprite1.draw();
        bmf1Sprite.draw();
        bmf2Sprite.draw("HELLO WORLD");
        uvCube->bind();
        model1.draw();

        GLfloat currTime = window.getRunningTimeAsSeconds();

        model2.getShader()->run();
        model2.getShader()->setUniform("time", currTime);
        uvSword->bind();
        model2.draw();
        window.update();
    }
}
