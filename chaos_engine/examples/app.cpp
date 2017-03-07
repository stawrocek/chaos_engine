#include "app.hpp"




ChaosExampleLibraryApp::ChaosExampleLibraryApp(){}

ChaosExampleLibraryApp::ChaosExampleLibraryApp(chaos::Window* w)
:Application(w)
{}

ChaosExampleLibraryApp::~ChaosExampleLibraryApp(){
/*#ifdef ANDROID
    FreeImage_DeInitialise();
#endif*/
}

void ChaosExampleLibraryApp::onCreate(){
    glEnable(GL_DEPTH_TEST);
/*#ifdef ANDROID
    FreeImage_Initialise(false);
#endif*/
    renderer = new chaos::Renderer(window);
    resourceManager = new chaos::ResourceManager();
    sceneManager = new chaos::SceneManager(resourceManager, renderer);

    sceneManager->registerScene<ColorfulTriangles>("ColorfulTriangles");
    sceneManager->setActiveScene("ColorfulTriangles");
}

void ChaosExampleLibraryApp::onDraw(){
    sceneManager->runSceneFrame(0.001);
}

void ChaosExampleLibraryApp::onResize(int newWidth, int newHeight){

}

void ChaosExampleLibraryApp::run(){
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


