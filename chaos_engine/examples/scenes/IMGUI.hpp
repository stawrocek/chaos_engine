#ifndef IMGUITEST_HPP
#define IMGUITEST_HPP

#include "../../include/Scene.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Sprite.hpp"
#include "../../lib-loaders/ImGUI_Impl_Chaos.hpp"
#include "../../include/Primitives.hpp"

class ImGUITest: public chaos::Scene{
public:
    ImGUITest(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        rect = new chaos::Rectangle(renderer);
        rect->setScale(0.3, 0.3, 0.3);
        rect->setColor(1.0, 1.0, 0.0, 1.0);

        #if defined(__EMSCRIPTEN__)
        //no .jpg support on windows for now ;/
        textureTestJPG = resourceManager->loadResource("files/textures/composition-a-1923-piet-mondrian.png", "pietJPG");
        #else
        textureTestJPG = resourceManager->loadResource("files/textures/composition-a-1923-piet-mondrian.jpg", "pietJPG");
        #endif // __EMSCRIPTEN__
        textureTestPNG = resourceManager->loadResource("files/textures/composition-a-1923-piet-mondrian.png", "pietPNG");
        spriteLeft = new chaos::Sprite(renderer, textureTestJPG);
        spriteRight = new chaos::Sprite(renderer, textureTestPNG);
        spriteLeft->setScale(0.2, 0.2, 0.2);
        spriteRight->setScale(0.2, 0.2, 0.2);
        spriteLeft->moveX(-0.3);
        spriteRight->moveX(0.3);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        window->clearColor(0.2, 0.7, 0.2, 1.0);
        renderer->setCamCombined(glm::mat4(1));

        rect->rotateZ(deltaTime);
        if(!window->isTouched(chaos::TouchEvent::ButtonLeft)){
            rect->draw();
            spriteLeft->draw();
            spriteRight->draw();
        }
    }

    void onGUI(){
        {
            static float f = 0.0f;
            ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiSetCond_FirstUseEver);
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float *) &imClearColor);
            if (ImGui::Button("Test Window")) showTestWindow = !showTestWindow;
            if (ImGui::Button("Another Window")) showAnotherWindow = !showAnotherWindow;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // 2. Show another simple window, this time using an explicit Begin/End pair
        if (showAnotherWindow)
        {
            ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
            ImGui::Begin("Another Window", &showAnotherWindow);
            ImGui::Text("Hello");
            ImGui::End();
        }

        // 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
        if (showTestWindow)
        {
            ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
            ImGui::ShowTestWindow(&showTestWindow);
        }
    }

    void deliverEvent(chaos::Event* event){

    }

private:
    chaos::Rectangle* rect=nullptr;
    chaos::Texture* textureTestJPG=nullptr;
    chaos::Texture* textureTestPNG=nullptr;
    chaos::Sprite* spriteLeft=nullptr;
    chaos::Sprite* spriteRight=nullptr;
    bool showTestWindow = true;
    bool showAnotherWindow = false;
    ImVec4 imClearColor;
};

#endif // IMGUITEST_HPP
