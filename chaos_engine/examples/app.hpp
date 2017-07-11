#ifndef BASIC_APP
#define BASIC_APP

#ifdef ANDROID
#define CHAOS_PLATFORM_ANDROID
#include <android/asset_manager.h>
#include <vector>
#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"
#include "../../include/glm/gtx/rotate_vector.hpp"
#include "../../include/glm/gtx/string_cast.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"

#include "../../include/Window.hpp"
#include "../../include/Application.hpp"
#include "../../include/ShaderProgram.hpp"
#include "../../include/VertexArray.hpp"
#include "../../include/Transform.hpp"
#include "../../include/Renderer.hpp"
#include "../../include/ResourceManager.hpp"
#include "../../include/SceneManager.hpp"
#include "../../include/Logger.hpp"

#else

#include "../include/Renderer.hpp"
#include "../include/Application.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/SceneManager.hpp"
#include "../include/Logger.hpp"
#include "../include/Texture.hpp"
#endif


#include "scenes/Transforms.hpp"
//#include "scenes/VAOnShaders.hpp"
//#include "scenes/Gizmos.hpp"
//#include "scenes/Lighting.hpp"
//#include "scenes/Rubik.hpp"
#include "scenes/IMGUI.hpp"

#ifdef __EMSCRIPTEN__
#include "../lib-loaders/SDL_Texture_Loader.hpp"
#else
#include "../lib-loaders/FreeImageTextureLoader.hpp"
#endif //texture-loaders

class ChaosExampleLibraryApp: public chaos::Application{
public:
    ChaosExampleLibraryApp();                             //Android
    ChaosExampleLibraryApp(chaos::Window* w);             //PC
    ~ChaosExampleLibraryApp();

    void onCreate();
    void onDraw();
    void onResize(int newWidth, int newHeight);

    void run();
    void runEvents();
    bool mainLoop = true;

    chaos::SceneManager* sceneManager = nullptr;
    chaos::ResourceManager* resourceManager=nullptr;
    chaos::Renderer* renderer=nullptr;
    chaos::TextureLoader* textureLoader = nullptr;
};

#endif //BASIC_APP

