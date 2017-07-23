#include "../include/Resource.hpp"

chaos::Resource::Resource(std::string fpath){
    fpathDeviceDependent = chaos::Application::getDataStorageDirectory()+fpath;
}

std::string chaos::Resource::getFilePath(){
    return fpathDeviceDependent;
}

chaos::Resource::Resource(){}

chaos::Resource::~Resource(){}
