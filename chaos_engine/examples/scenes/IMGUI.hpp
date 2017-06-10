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
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        window->clearColor(0.2, 0.7, 0.2, 1.0);
        renderer->setCamCombined(glm::mat4(1));

        rect->rotateZ(deltaTime);
        rect->draw();
    }

    void onGUI(){
        {
            bool show_another_window=false;
            bool show_test_window=true;
            static ImVec4 clear_color = ImColor(114, 144, 154);
            static float f = 0.0f;
            ImGui::Text("Hello, world!");
            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("clear color", (float*)&clear_color);
            if (ImGui::Button("Test Window")) show_test_window ^= 1;
            if (ImGui::Button("Another Window")) show_another_window ^= 1;
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            static char strInput[256];
            ImGui::InputText("Window title", strInput, 255);
        }
    }

    void deliverEvent(chaos::Event* event){

    }

private:
    chaos::Rectangle* rect=nullptr;
    bool show_test_window = true;
    bool show_another_window = false;
};

#endif // IMGUITEST_HPP
