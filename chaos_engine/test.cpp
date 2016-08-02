#include <iostream>

#include "include/Window.hpp"
#include "include/InputHandler.hpp"
#include "include/Transform.hpp"
#include "include/ShaderProgram.hpp"
#include "include/Texture.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    chaos::WindowStyle style("Test 1", 100, 100, 600, 480, SDL_WINDOW_OPENGL);
    chaos::Window window(style);
    chaos::Transform testTransform;
    testTransform.setScale(0.5f, 0.5f, 0.5f);
    chaos::Texture texture1("files/textures/composition-a-1923-piet-mondrian.jpg");

    //chaos::Texture texture1("files/textures/awesomeface.png");

    GLfloat vertices[] = {
        -1.f, -1.f, 0.f,
        1.f, -1.f, 0.f,
        -1.f,  1.f, 0.f,
        1.f, 1.f, 0.f,
        1.f, -1.f, 0.f,
        -1.f,  1.f, 0.f
    };

    GLfloat uvVerts[] = {
        0.f, 0.f,
        1.f, 0.f,
        0.f, 1.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 1.f
    };

    chaos::ShaderProgram shaderProgram{std::make_pair("files/shaders/shader1.vs", GL_VERTEX_SHADER),
                                       std::make_pair("files/shaders/shader1.fs", GL_FRAGMENT_SHADER)};

    GLuint vboVX, VAO, vboUV;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vboVX);
    glGenBuffers(1, &vboUV);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vboVX);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboUV);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvVerts), uvVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLboolean mainLoop=true;
    GLfloat r=0.0;

    while (mainLoop){
	    window.clearColor(r, 0.4, 0.0, 1.0);
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

		if(inputHandler.isKeyDown('r')){
            if(r+0.0001 <= 1.0)
            r+=0.0001;
		}
		if(inputHandler.isKeyDown('e')){
		    if(r-0.0001 >= 0.0)
            r-=0.0001;
		}
		GLfloat deltaTime = window.getDeltaTime();

        if(inputHandler.isKeyDown('a')){
            testTransform.moveX(-1.f * deltaTime);
        }
        if(inputHandler.isKeyDown('d')){
            testTransform.moveX(+1.f * deltaTime);
        }
        if(inputHandler.isKeyDown('w')){
            testTransform.moveY(+1.f * deltaTime);
        }
        if(inputHandler.isKeyDown('s')){
            testTransform.moveY(-1.f * deltaTime);
        }

        shaderProgram.run();

        GLfloat greenValue = 0.5;
        texture1.use(GL_TEXTURE1);
        shaderProgram.setUniform("ourColor", glm::vec4(0.0, r, 0.0, 1.0));
        shaderProgram.setUniform("mx", testTransform.getGlobalTransformMatrix());
        shaderProgram.setUniform("tex0", texture1.getId());

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);


        window.update();
    }
}
