#include <iostream>

#include "include/Window.hpp"
#include "include/InputHandler.hpp"
#include "include/Transform.hpp"
#include "include/ShaderProgram.hpp"

static chaos::InputHandler& inputHandler = chaos::InputHandler::getInstance();

int main(int argc, char* argv[]){
    chaos::WindowStyle style("Test 1", 100, 100, 600, 480, SDL_WINDOW_OPENGL);
    chaos::Window window(style);
    chaos::Transform testTransform;
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    chaos::ShaderProgram shaderProgram{std::make_pair("files/shaders/shader1.vs", GL_VERTEX_SHADER),
                                       std::make_pair("files/shaders/shader1.fs", GL_FRAGMENT_SHADER)};

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

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
        if(inputHandler.isKeyDown('a')){
            testTransform.moveX(-0.001f);
        }
        if(inputHandler.isKeyDown('d')){
            testTransform.moveX(+0.001f);
        }
        if(inputHandler.isKeyDown('w')){
            testTransform.moveY(+0.001f);
        }
        if(inputHandler.isKeyDown('s')){
            testTransform.moveY(-0.001f);
        }

        shaderProgram.run();

        // Update the uniform color
        GLfloat greenValue = 0.5;
        //GLint vertexColorLocation = glGetUniformLocation(shaderProgram.getId(), "ourColor");
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        shaderProgram.setUniform("ourColor", glm::vec4(0.0, 0.5, 0.0, 1.0));
        shaderProgram.setUniform("mx", testTransform.getGlobalTransformMatrix());

        // Draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        window.swapBuffers();
    }
}
