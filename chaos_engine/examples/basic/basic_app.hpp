#ifndef BASIC_APP
#define BASIC_APP

#ifdef ANDROID
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
#include "../../../include/Application.hpp"
#include "../../../include/ShaderProgram.hpp"
#include "../../../include/VertexArray.hpp"
#include "../../../include/Transform.hpp"
#include "../../../include/Renderer.hpp"
#include "../../../include/ResourceManager.hpp"
#include "../../../include/MeshPrefab.hpp"
#include "../../../include/Model.hpp"
#include "../../../include/primitives.hpp"
#include "../../../include/Texture.hpp"
#include "../../../include/Camera.hpp"
#include "../../../include/Sprite.hpp"

#else

#include "../include/Application.hpp"
#include "../include/Renderer.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/primitives.hpp"
#include "../include/MeshPrefab.hpp"
#include "../include/Model.hpp"
#include "../include/Texture.hpp"
#include "../include/Camera.hpp"
#include "../include/Event.hpp"
#include "../include/Sprite.hpp"
#endif

class BasicApplication: public chaos::Application{
public:
    BasicApplication();                             //Android
    BasicApplication(chaos::Window* w);             //PC
    ~BasicApplication();

    void onCreate();
    void onDraw();
    void onResize(int newWidth, int newHeight);

    void run();
    bool mainLoop = true;
    chaos::ResourceManager* resourceManager=nullptr;

    chaos::Renderer* renderer=nullptr;
    chaos::Cube* cube=nullptr;
    chaos::Model* modelSkeleton=nullptr;
    chaos::Model* modelChest=nullptr;
    chaos::MeshPrefab* meshSkeleton=nullptr;
    chaos::MeshPrefab* meshChest=nullptr;
    chaos::Texture* textureSkeleton=nullptr;
    chaos::Texture* textureChest=nullptr;
    chaos::Texture* texturePiet=nullptr;

    chaos::Camera* cam = nullptr;
    chaos::Sprite* spritePiet = nullptr;
};

#endif //BASIC_APP
