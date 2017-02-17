
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
#include "../../../include/Renderer.hpp"
#include "../../../include/ResourceManager.hpp"
#include "../../../include/MeshPrefab.hpp"
#include "../../../include/Model.hpp"
#include "../../../include/primitives.hpp"
#include "../../../include/Texture.hpp"

#endif // CHAOS_PLATFORM_PC

#ifdef CHAOS_PLATFORM_PC
#include "../include/Application.hpp"
#include "../include/Renderer.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/primitives.hpp"
#include "../include/MeshPrefab.hpp"
#include "../include/Model.hpp"
#include "../include/Texture.hpp"
#endif

class BasicApplication: public chaos::Application{
public:
    BasicApplication(){}

    BasicApplication(chaos::Window* w)
    :Application(w)
    {}

    ~BasicApplication(){
        #ifdef ANDROID
        FreeImage_DeInitialise();
        #endif
    }

    void onCreate(){
        #ifdef ANDROID
        FreeImage_Initialise(false);
        #endif
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
            vertexSource = chaos::Shader::translateGL3ShaderGLES2Shader(vertexSource, GL_VERTEX_SHADER);
            fragmentSource = chaos::Shader::translateGL3ShaderGLES2Shader(fragmentSource, GL_FRAGMENT_SHADER);
        #endif

        txTest = new chaos::Transform();
        txTest->setScale(0.1, 0.1, 0.1);
        chaos::Shader shVertex;
        shVertex.loadFromString(vertexSource,GL_VERTEX_SHADER);
        chaos::Shader shFragment;
        shFragment.loadFromString(fragmentSource,GL_FRAGMENT_SHADER);
        shr = new chaos::ShaderProgram({shVertex, shFragment});
        vao = new chaos::VertexArray(3, 0, 0, 0, &rect_Pos);
        renderer = new chaos::Renderer(window);
        resourceManager = new chaos::ResourceManager();
        cube=new chaos::Cube(renderer);
        cube->setScale(0.1, 0.1, 0.1);
        cube->setColor(0.4f,0.4f,0.0f,1.0f);
        cube->moveX(0.5);
        cube->rotateZ(M_PI/4.0f);
        meshSkeleton = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/skeleton.obj", "skeleton");
        renderer->addMeshVAO(meshSkeleton);
        meshChest = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/Chest3.obj", "chest");
        renderer->addMeshVAO(meshChest);

        modelSkeleton = new chaos::Model(renderer, meshSkeleton);
        modelSkeleton->setScale(0.02,0.02,0.02);
        modelSkeleton->setColor(1.0,0.1,0.1,1.0);

        modelChest = new chaos::Model(renderer, meshChest);
        modelChest->setScale(0.02,0.02,0.02);

        textureSkeleton = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/skeletonUV.png", "uvMap:Skeleton");
        textureChest = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/chestUV.png", "uvMap:Chest");
    }

    void onDraw(){
        cube->rotateY(0.01);
        modelSkeleton->rotateY(0.01);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.2f, 1.0f);
        shr->run();
        shr->setUniform("uniColor", glm::vec4(1,1,0,1));
        shr->setUniform("mx", txTest->getGlobalTransformMatrix());
        vao->bind();
        vao->draw(shr);
        vao->bind();
        glUseProgram (0);
        cube->draw();
        textureSkeleton->bind();
        modelSkeleton->draw();
        textureChest->bind();
        modelChest->draw();
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
    chaos::Cube* cube=nullptr;
    chaos::ResourceManager* resourceManager=nullptr;
    chaos::Model* modelSkeleton=nullptr;
    chaos::Model* modelChest=nullptr;
    chaos::MeshPrefab* meshSkeleton=nullptr;
    chaos::MeshPrefab* meshChest=nullptr;
    chaos::Texture* textureSkeleton=nullptr;
    chaos::Texture* textureChest=nullptr;
};
