#include "basic_app.hpp"

BasicApplication::BasicApplication(){}

BasicApplication::BasicApplication(chaos::Window* w)
:Application(w)
{}

BasicApplication::~BasicApplication(){
    #ifdef ANDROID
    FreeImage_DeInitialise();
    #endif
}

void BasicApplication::onCreate(){
    glEnable(GL_DEPTH_TEST);

    #ifdef ANDROID
    FreeImage_Initialise(false);
    #endif

    resourceManager = new chaos::ResourceManager();
    texturePiet = resourceManager->loadResource<chaos::Texture>("files/textures/composition-a-1923-piet-mondrian.jpg", "piet");
    renderer = new chaos::Renderer(window);

    cube=new chaos::Cube(renderer);
    cube->setScale(0.1, 0.1, 0.1);
    cube->setColor(0.4f,0.4f,0.0f,1.0f);
    cube->moveX(0.5);
    cube->rotateZ(PI/4.0f);

    #ifdef ANDROID
        LOGI("BASIC_APP says: width: %d, height: %d", window->getStyle().width, window->getStyle().height);
    #else
    std::cout << window->getStyle().width << " / " << window->getStyle().height << "\n";
    #endif // ANDROID


    cam = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getWidth()/window->getHeight(), 0.1f, 100.0f));
    cam->moveY(0.35f);
    cam->moveZ(2.0f);

    meshSkeleton = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/skeleton.obj", "skeleton");
    renderer->addMeshVAO(meshSkeleton);
    meshChest = resourceManager->loadResource<chaos::MeshPrefab>("files/models3d/Chest3.obj", "chest");
    renderer->addMeshVAO(meshChest);

    modelSkeleton = new chaos::Model(renderer, meshSkeleton);
    modelSkeleton->setScale(0.03,0.03,0.03);
    modelSkeleton->setColor(0.7,0.7,0.7,0.7);

    modelChest = new chaos::Model(renderer, meshChest);
    modelChest->setScale(0.03,0.03,0.03);

    textureSkeleton = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/skeletonUV.png", "uvMap:Skeleton");
    textureChest = resourceManager->loadResource<chaos::Texture>("files/textures/uv_maps/chestUV.png", "uvMap:Chest");
    spritePiet = new chaos::Sprite(renderer, texturePiet);
}

void BasicApplication::onDraw(){
    cube->rotateY(0.01);
    modelChest->rotateY(0.001);
    spritePiet->rotateY(0.001);
    cam->moveZ(-0.0003);
    modelSkeleton->rotateY(0.001);

    renderer->setCamCombined(cam->getProjectionMatrix()*cam->getViewMatrix());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.6f, 0.2f, 1.0f);
    cube->draw();
    spritePiet->draw();
    textureSkeleton->bind();
    /*LOGI("draw model skeleton, (%d,%d,%d,%d)", modelSkeleton->getVertexArray()->getVerticesSize(),
         modelSkeleton->getVertexArray()->getNormalsSize(), modelSkeleton->getVertexArray()->getUVSize(),
         modelSkeleton->getVertexArray()->getDataSize());*/
    modelSkeleton->draw();
    textureChest->bind();
    glm::vec3 chestScale = modelChest->getScale();
    glm::vec3 chestScaleBP = chestScale;
    for(int i = -2; i <= 2; i++){
        modelChest->setX(i*0.5);
        chestScale*=1.1;
        modelChest->setScale(chestScale);
        modelChest->draw();
    }
    modelChest->setScale(chestScaleBP);
    spritePiet->draw();
}

void BasicApplication::onResize(int newWidth, int newHeight){

}

void BasicApplication::run(){
    #ifndef ANDROID
    onCreate();
    while (mainLoop){
        //window->clearColor(0.2, 0.4, 0.6, 1.0);
        SDL_Event event;
        while (SDL_PollEvent(&event)){
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

