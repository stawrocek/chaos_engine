#include "../include/Application.hpp"

std::string chaos::Application::dataStorageDir="";

void chaos::Application::setWindow(Window* w){
    window=w;
}

chaos::Application::Application(){}
chaos::Application::Application(Window* w)
:window(w)
{};

void chaos::Application::onCreate(){};
void chaos::Application::onDraw(){};
void chaos::Application::onResize(int newWidth, int newHeight){};
void chaos::Application::run(){};

std::string const& chaos::Application::getDataStorageDirectory(){
    return dataStorageDir;
}

void chaos::Application::setDataStorageDirectory(std::string str){
    dataStorageDir = str;
}
