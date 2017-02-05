
#ifndef CHAOS_PLATFORM_PC
#define CHAOS_PLATFORM_ANDROID
#include <android/log.h>
#include <android/asset_manager.h>
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
//#include "../../../include/Renderer.hpp"
#include "../../../include/primitives.hpp"

#endif // CHAOS_PLATFORM_PC

#ifdef CHAOS_PLATFORM_PC
#include "../include/Application.hpp"
#include "../include/Renderer.hpp"
#include "../include/primitives.hpp"
#endif

class BasicApplication: public chaos::Application{
public:
    BasicApplication(){}

    BasicApplication(chaos::Window* w)
    :Application(w)
    {}

    void onCreate(){
        const GLubyte* glVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        #ifdef ANDROID
            LOGI("glVersion (onCreate): %s", glVersion);
        #else
            std::cout << "glVersion: " << glVersion << "\n";
        #endif

        glEnable(GL_DEPTH_TEST);
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
                    //"out int test;\n"
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
                    //" texture = test;\n"
                    "}\n";

        //std::string vertexSource2 = chaos::Shader::translateGL3ShaderGLES2Shader(vertexSource, GL_VERTEX_SHADER);
        //std::string fragmentSource2 = chaos::Shader::translateGL3ShaderGLES2Shader(fragmentSource, GL_FRAGMENT_SHADER);
        //std::cout << vertexSource2 << "\n\n" << fragmentSource2 << "\n";

        #ifdef ANDROID
            vertexSource = chaos::Shader::translateGL3ShaderGLES2Shader(vertexSource, GL_VERTEX_SHADER);
            fragmentSource = chaos::Shader::translateGL3ShaderGLES2Shader(fragmentSource, GL_FRAGMENT_SHADER);
        #endif


        //gles 2
        /*#ifdef ANDROID
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
        #endif // ANDROID*/

        txTest = new chaos::Transform();
        txTest->setScale(0.1, 0.1, 0.1);
        chaos::Shader shVertex;
        shVertex.loadFromString(vertexSource,GL_VERTEX_SHADER);
        chaos::Shader shFragment;
        shFragment.loadFromString(fragmentSource,GL_FRAGMENT_SHADER);
        shr = new chaos::ShaderProgram({shVertex, shFragment});
        vao = new chaos::VertexArray(3, 0, 0, 0, &rect_Pos);
        renderer = new chaos::Renderer(window);
        /*cube=new chaos::Cube(renderer);
        cube->setScale(0.1, 0.1, 0.1);
        cube->setColor(0.4f,0.4f,0.0f,1.0f);
        cube->moveX(0.5);
        cube->rotateZ(M_PI/4.0f);*/
    }

    void onDraw(){
        //LOGI("data storage: %s", Application::dataStorageDir.c_str());
        //Application::dataStorageDir = "cokolwiek";
        //LOGI("data storage 2: %s", Application::dataStorageDir.c_str());
        //cube->rotateY(0.01);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.2f, 1.0f);
        shr->run();
        shr->setUniform("uniColor", glm::vec4(1,1,0,1));
        shr->setUniform("mx", txTest->getGlobalTransformMatrix());
        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vao->countVertices());
        vao->bind();
        glUseProgram (0);
        //cube->draw();
    }

    void run(){
        #ifndef ANDROID
        onCreate();
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
    chaos::Renderer* renderer=nullptr;
    //chaos::Cube* cube=nullptr;
};
