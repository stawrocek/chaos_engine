#include "../include/Resource.hpp"

chaos::Resource::Resource(std::string& fpath){
    fpath = chaos::Application::getDataStorageDirectory()+fpath;
}

chaos::Resource::~Resource(){}
