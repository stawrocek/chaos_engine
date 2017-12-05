#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP

/*
    Basic example of Transforms parenting
*/
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "../../include/Scene.hpp"
#include "../../include/Primitives.hpp"
#include "../../include/Camera.hpp"
#include "../../include/CubeMap.hpp"
#include "../../include/Skybox.hpp"
#include "../../include/FBO.hpp"
#include "../../include/Sprite.hpp"
#include "../../include/Water.hpp"
#include "../../include/TerrainPrefab.hpp"
#include "../../include/Terrain.hpp"
#include "../../include/Logger.hpp"
#include "../../lib-loaders/ImGUI_Impl_Chaos.hpp"

class Transforms: public chaos::Scene{
public:
    Transforms(std::string _name)
    :Scene(_name)
    {}

    ~Transforms(){
        for(int i = 0; i < vecCubes.size(); i++){
            delete vecCubes[i];
        }
    }

    void onSceneLoadToMemory(){
        srand(time(NULL));
        vecCubes.resize(10);
        for(int i = 0; i < 10; i++){
            vecCubes[i] = new chaos::Cube(renderer);
            vecCubes[i]->moveX(2*i);
            vecCubes[i]->setColor(i/10.0, 0, 0, 1);
            if(i != 0){
                vecCubes[i]->setParent(vecCubes[i-1]);
            }
        }
        vecCubes.front()->setScale(0.01, 0.01, 0.01);

        camera = new chaos::Camera(renderer, chaos::PERSPECTIVE, glm::perspective(glm::radians(45.0f), (GLfloat)window->getStyle().width/window->getStyle().height, 0.1f, 100.0f));
        //camera->moveZ(1.0);
        window->setRelativeMode(true);

        skyboxTexture = resourceManager->loadResource("files/textures/skyboxes/skybox1/",
                        {"right.jpg","left.jpg","top.jpg","bottom.jpg","back.jpg","front.jpg"},"skybox1");
        //skyboxTexture = resourceManager->loadResource("files/textures/",
        //                {"brick.png","brick.png","brick.png","brick.png","brick.png","brick.png"},"skybox1");
        textureBlendMap = resourceManager->loadResource("files/textures/terrain_maps/blendmap2.png", "blendmap");
        textureFlowers = resourceManager->loadResource("files/textures/terrain_maps/grassFlowers.png", "flowers");
        textureGrass = resourceManager->loadResource("files/textures/terrain_maps/grass.png", "grass");
        textureSand = resourceManager->loadResource("files/textures/terrain_maps/sand.png", "sand");
        texturePath = resourceManager->loadResource("files/textures/brick.png", "path");
        skybox = new chaos::Skybox(renderer, skyboxTexture);
        skybox->rotateZ(3.1415);
        water = new chaos::Water(renderer, camera);
        water->setRotX(3.1415/2.0);
        water->moveY(-0.5);
        reflectionTexture = water->getReflectionFBO()->getTexture(0);
        refractionTexture = water->getRefractionFBO()->getTexture(0);
        reflectionSprite = new chaos::Sprite(renderer, reflectionTexture);
        refractionSprite = new chaos::Sprite(renderer, refractionTexture);
        reflectionSprite->setParent(camera);
        refractionSprite->setParent(camera);
        reflectionSprite->setScale(0.4, 0.4, 0.4);
        refractionSprite->setScale(0.4, 0.4, 0.4);
        reflectionSprite->moveZ(-3);
        refractionSprite->moveZ(-3);
        reflectionSprite->moveX(-1);
        refractionSprite->moveX(1);
        heightmap = resourceManager->loadResource("files/textures/heightmaps/valley.png", "heightmapTest");
        terrainPrefab = resourceManager->loadResource(heightmap, 0, 2, "terrain");
        renderer->addTerrainVAO(terrainPrefab);
        terrain = new chaos::Terrain(renderer, terrainPrefab, {
                {chaos::Terrain::BLEND_MAP, textureBlendMap},
                {chaos::Terrain::BACKGROUND, textureSand},
                {chaos::Terrain::TEXTURE_R, texturePath},
                {chaos::Terrain::TEXTURE_G, textureGrass},
                {chaos::Terrain::TEXTURE_B, textureFlowers}
            });
    }

    void onSceneActivate(){

    }

    void update(GLfloat deltaTime){
        if(window->isKeyDown(chaos::KeyboardEvent::KeyA))
            camera->processKeyboard(chaos::LEFT, deltaTime*cameraMoveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyD))
            camera->processKeyboard(chaos::RIGHT, deltaTime*cameraMoveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyW))
            camera->processKeyboard(chaos::FORWARD, deltaTime*cameraMoveSpeed);
        if(window->isKeyDown(chaos::KeyboardEvent::KeyS))
            camera->processKeyboard(chaos::BACKWARD, deltaTime*cameraMoveSpeed);
        for(int i = 0; i < vecCubes.size(); i++){
            if(i%3 == 0)
                vecCubes[i]->rotateZ(rotSpeed);
            if(i%3 == 1)
                vecCubes[i]->rotateY(rotSpeed);
            if(i%3 == 2)
                vecCubes[i]->rotateX(rotSpeed);
        }
    }

    void draw(GLfloat deltaTime){
        double reflectionMoveDistance = 2.0*(camera->getY() - water->getY());
        water->getReflectionFBO()->bind();
        camera->moveY(-reflectionMoveDistance);
        camera->invertPitch();
        renderer->setCamCombined(camera);
        drawScene();
        camera->moveY(reflectionMoveDistance);
        camera->invertPitch();
        renderer->setCamCombined(camera);
        water->getRefractionFBO()->bind();
        drawScene();

        water->getRefractionFBO()->unbind();
        drawScene();
        water->draw();
        if(window->isKeyDown(chaos::KeyboardEvent::KeyP)){
            reflectionSprite->draw();
        }
        if(window->isKeyDown(chaos::KeyboardEvent::KeyR)){
            refractionSprite->draw();
        }
        if(window->isKeyDown(chaos::KeyboardEvent::KeyQ)){
            water->moveY(-0.005);
        }
        if(window->isKeyDown(chaos::KeyboardEvent::KeyE)){
            water->moveY(0.005);
        }
    }

    void drawScene(){
        window->clearColor(0.2, 0.2, 0.7, 1.0);
        skybox->draw();
        terrain->draw();
        for(auto cb: vecCubes)
            cb->draw();
    }

    void onGUI(){
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(100,50));
        ImGui::Begin("fps window");
        ImGui::Text("fps, %d", window->getFPS());
        ImGui::End();
    }

    void deliverEvent(chaos::Event* event){
        if(event->type == chaos::Event::MouseMotion){
            camera->processMouse(event->motionEvent.relX, -event->motionEvent.relY);
        }
        if(event->type == chaos::Event::KeyDown && event->keyEvent.keyCode == chaos::KeyboardEvent::KeyC){
            water->scaleUp(2,1,2);
        }
    }

private:
    std::vector<chaos::Cube*> vecCubes;
    chaos::Camera* camera=nullptr;
    GLfloat cameraMoveSpeed=5.0f;
    GLfloat rotSpeed = 0.001;
    chaos::CubeMap* skyboxTexture=nullptr;
    chaos::Skybox* skybox=nullptr;
    chaos::Texture* reflectionTexture=nullptr;
    chaos::Texture* refractionTexture=nullptr;
    chaos::Sprite* reflectionSprite=nullptr;
    chaos::Sprite* refractionSprite=nullptr;
    chaos::Water* water=nullptr;
    chaos::TerrainPrefab* terrainPrefab=nullptr;
    chaos::Texture* heightmap=nullptr;
    chaos::Terrain* terrain=nullptr;
    chaos::Texture* textureBlendMap;
    chaos::Texture* textureGrass;
    chaos::Texture* texturePath;
    chaos::Texture* textureFlowers;
    chaos::Texture* textureSand;
};

#endif // VAONSHADERS_HPP


