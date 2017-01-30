
#ifndef CHAOS_PLATFORM_PC
#define CHAOS_PLATFORM_ANDROID
#include <GLES2/gl2.h>
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,"Chaos", __VA_ARGS__))
#include "../../../include/Window.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../../include/ShaderProgram.hpp"
#include "../../../include/VertexArray.hpp"
#include "../../../include/Transform.hpp"
#endif // CHAOS_PLATFORM_PC

#ifdef CHAOS_PLATFORM_PC
#include "../include/Application.hpp"
#endif

class BasicApplication: public chaos::Application{
public:
    BasicApplication(){
        onCreate();
    }

    BasicApplication(chaos::Window* w)
    :Application(w)
    {
        onCreate();
    }

    void onCreate(){
        std::vector<GLfloat> rect_Pos = {
            -1.f, -1.f, 0.f,
             1.f, -1.f, 0.f,
            -1.f,  1.f, 0.f,
             1.f,  1.f, 0.f,
             1.f, -1.f, 0.f,
            -1.f,  1.f, 0.f
        };
        std::string vertexSource=
                    "#version 330 core\n"
                    "layout (location = 0) in vec3 position;\n"
                    "uniform mat4 mx;\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = mx*vec4(position, 1.0);\n"
                    "}\n";
        std::string fragmentSource=
                    "#version 330 core\n"
                    "out vec4 color;\n"
                    "uniform vec4 uniColor;\n"
                    "void main(){\n"
                    "    color = uniColor;\n"
                    "}\n";
        #ifdef ANDROID
        vertexSource=
                    "#version 100\n"
                    "precision highp float;\n"
                    "attribute vec3 position;\n"
                    "uniform mat4 mx;\n"
                    "void main()\n"
                    "{\n"
                    "    gl_Position = mx*vec4(position, 1.0);\n"
                    "}\n";
        fragmentSource=
                    "#version 100\n"
                    "precision highp float;\n"
                    "uniform vec4 uniColor;\n"
                    "void main(){\n"
                    "    gl_FragColor = uniColor;\n"
                    "}\n";
        #endif // ANDROID

        txTest = new chaos::Transform();
        txTest->setScale(0.1, 0.1, 0.1);
        chaos::Shader shVertex;
        shVertex.loadFromString(vertexSource,GL_VERTEX_SHADER);
        chaos::Shader shFragment;
        shFragment.loadFromString(fragmentSource,GL_FRAGMENT_SHADER);
        shr = new chaos::ShaderProgram({shVertex, shFragment});
        vao = new chaos::VertexArray(3, 0, 0, 0, &rect_Pos);
    }

    void onDraw(){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.2f, 1.0f);
        shr->run();
        shr->setUniform("uniColor", glm::vec4(1,1,0,1));
        shr->setUniform("mx", txTest->getGlobalTransformMatrix());
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vao->countVertices());
        vao->bind();
        glUseProgram (0);
    }

    void run(){
        #ifndef ANDROID
        while (mainLoop){
            window->clearColor(0.2, 0.4, 0.6, 1.0);
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
            }

            GLfloat deltaTime = window->getDeltaTime();
            onDraw();

            window->update();
        }
        #endif
    }
    bool mainLoop = true;
    chaos::ShaderProgram* shr=nullptr;
    chaos::Transform* txTest=nullptr;
    chaos::VertexArray* vao=nullptr;
};
