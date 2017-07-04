#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <iostream>

#include "Export.hpp"
#include "Resource.hpp"
#include "Texture.hpp"
#include "Logger.hpp"

namespace chaos{

class CHAOS_EXPORT ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager();
    template <typename T>
    T* loadResource(std::string fpath, std::string id){
        if(cache.find(id) != cache.end()){
            return dynamic_cast<T*>(cache[id]);
        }
        T* tmp = new T(fpath);
        cache[id] = tmp;
        return tmp;
    }
    chaos::Texture* loadResource(std::string fpath, std::string id){
        SHOUT("loading texture!\n");
        if(cache.find(id) != cache.end()){
            return dynamic_cast<chaos::Texture*>(cache[id]);
        }
        chaos::Texture* tmp = new chaos::Texture(fpath, textureLoader);
        cache[id] = tmp;
        return tmp;
    }
    template <typename T>
    T* getResource(std::string id){
        if(cache.find(id) == cache.end()){
            return nullptr;
        }
        return dynamic_cast<T*>(cache[id]);
    }
    template <typename T>
    void removeResource(std::string id){
        if(cache.find(id) != cache.end()){
            delete cache[id];
            cache.erase(id);
        }
    }

    TextureLoader* getTextureLoader(){
        return textureLoader;
    }

    void setTextureLoader(TextureLoader* _textureLoader){
        textureLoader = _textureLoader;
    }

protected:
    std::unordered_map<std::string, Resource*> cache;
    TextureLoader* textureLoader=nullptr;
};

}
#endif // RESOURCEMANAGER_HPP
