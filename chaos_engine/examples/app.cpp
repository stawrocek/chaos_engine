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
#ifdef TEXTURES_FREEIMAGE
    textureLoader = new FreeImageTextureLoader();
#endif
#ifdef TEXTURES_SDLIMAGE
    textureLoader = new SDLTextureLoader();
#endif
    if(textureLoader == nullptr){
        SHOUT("texture laoder not initialized!\n");
    }
/*#if defined(TEXTURES_SDLIMAGE) && !defined (__EMSCRIPTEN__)

#endif*/
    renderer = new chaos::Renderer(window);
    resourceManager = new chaos::ResourceManager();
    sceneManager = new chaos::SceneManager(resourceManager, renderer);

    resourceManager->setTextureLoader(textureLoader);

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


