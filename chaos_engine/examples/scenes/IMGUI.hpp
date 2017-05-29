#ifndef IMGUITEST_HPP
#define IMGUITEST_HPP

#include "../../include/Scene.hpp"
#include "../../include/Texture.hpp"
#include "../../include/Sprite.hpp"

#include "../../include/ImGUI_Impl_Chaos.hpp"

class ImGUITest: public chaos::Scene{
public:
    ImGUITest(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        rect = new chaos::Rectangle(renderer);
        rect->setScale(0.3, 0.3, 0.3);
        rect->setColor(1.0, 1.0, 0.0, 1.0);
        //chaos::SDL2Window* w = dynamic_cast<chaos::SDL2Window*>(window);
        ImGui_ImplChaos_Init(window);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        ImGui_ImplChaos_NewFrame(window);
        static float f = 0.0f;
        ImGui::Text("Hello, world!");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        //ImGui::ColorEdit3("clear color", (float*)&clear_color);
        if (ImGui::Button("Test Window")) show_test_window ^= 1;
        if (ImGui::Button("Another Window")) show_another_window ^= 1;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);



        window->clearColor(0.2, 0.7, 0.2, 1.0);
        renderer->setCamCombined(glm::mat4(1));
        rect->rotateZ(deltaTime);
        rect->draw();

        ImGui::Render();
    }

    void deliverEvent(chaos::Event* event){
    }

private:
    chaos::Rectangle* rect=nullptr;
    bool show_test_window = true;
    bool show_another_window = false;
};

#endif // IMGUITEST_HPP
