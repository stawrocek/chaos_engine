#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <string>

#include "Scene.hpp"

class MainMenu: public chaos::Scene{
public:
    MainMenu(std::string _name)
    :Scene(_name)
    {
        std::cout << "Constructor of MainMenu\n";
    }

    virtual ~MainMenu(){
        std::cout << "Destructor of MainMenu\n";
    }

    virtual void onSceneActivate(){
        std::cout << "MainMenu::onSceneActivate()\n";
    };
    virtual void update(GLfloat deltaTime){
        //std::cout << "MainMenu::update(" << deltaTime << ")\n";
    }
    virtual void draw(GLfloat deltaTime){
        clearWindow(1.0, 0.0, 0.0, 1.0);
        //std::cout << "MainMenu::draw(" << deltaTime << ")\n";
    }
    virtual void deliverEvent(chaos::Event& e){
        //std::cout << "MainMenu::deliverEvent()\n";
        if(e.getChar() == 'n'){
            std::cout << "next!\n";
            scnManager->setActiveScene("Scene2");
        }
    }
    virtual void onSceneDeactivate(){
        std::cout << "MainMenu::onSceneDeactivate()\n";
    }
};

#endif // MAIN_MENU_HPP

