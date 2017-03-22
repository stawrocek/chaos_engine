#include "../include/ResourceManager.hpp"

chaos::ResourceManager::ResourceManager(){};

chaos::ResourceManager::~ResourceManager(){
    auto itr = cache.begin();
    while (itr != cache.end()) {
        delete itr->second;
        itr = cache.erase(itr);
    }
}
