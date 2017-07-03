#include "app.hpp"


ChaosExampleLibraryApp::ChaosExampleLibraryApp(){}

ChaosExampleLibraryApp::ChaosExampleLibraryApp(chaos::Window* w)
:Application(w)
{}

ChaosExampleLibraryApp::~ChaosExampleLibraryApp(){
#if defined(ANDROID) && defined(TEXTURES_FREEIMAGE)
    FreeImage_DeInitialise();
#endif
#if defined(TEXTURES_SDLIMAGE)
    IMG_Quit();
#endif // defined
}

void ChaosExampleLibraryApp::onCreate(){
    glEnable(GL_DEPTH_TEST);
#if defined(ANDROID) && defined(TEXTURES_FREEIMAGE)
    FreeImage_Initialise(false);
#endif
#if defined(TEXTURES_SDLIMAGE) && !defined (__EMSCRIPTEN__)
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
    else{
        printf("init ok\n");
    }
#endif
    renderer = new chaos::Renderer(window);
    resourceManager = new chaos::ResourceManager();
    sceneManager = new chaos::SceneManager(resourceManager, renderer);

    //sceneManager->registerScene<ColorfulTriangles>("ColorfulTriangles");
    sceneManager->registerScene<ImGUITest>("ImGUI");
    //sceneManager->registerScene<VAOnShaders>("VAOnShaders");
    //sceneManager->registerScene<GizmosTest>("GizmosTest");
    //sceneManager->registerScene<Rubik>("Rubik");
    sceneManager->setActiveScene("ImGUI");
}

void ChaosExampleLibraryApp::onDraw(){
    GLfloat deltaTime = window->getDeltaTime();
    runEvents();
    sceneManager->runSceneFrame(0.001);
    window->update();
}

void ChaosExampleLibraryApp::onResize(int newWidth, int newHeight){

}

void ChaosExampleLibraryApp::runEvents(){
    window->runEvents(sceneManager);
}

void ChaosExampleLibraryApp::run(){
    #ifndef ANDROID
    onCreate();
    while (mainLoop){
        onDraw();
    }
    #endif
}


