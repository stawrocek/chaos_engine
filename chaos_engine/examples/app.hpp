#ifndef BASIC_APP
#define BASIC_APP

#ifdef ANDROID
#define CHAOS_PLATFORM_ANDROID
#include <android/log.h>
#include <android/asset_manager.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,"Chaos", __VA_ARGS__))
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

#else

#include "../include/Renderer.hpp"
#include "../include/Application.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/SceneManager.hpp"
#endif

#include "scenes/ColorfulTriangles.hpp"
#include "scenes/VAOnShaders.hpp"
#include "scenes/Gizmos.hpp"
#include "scenes/ObjViewer.hpp"

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
};

#endif //BASIC_APP

