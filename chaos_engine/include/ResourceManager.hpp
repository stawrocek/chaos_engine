#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <iostream>
#include <initializer_list>

#include "Export.hpp"
#include "Resource.hpp"
#include "Texture.hpp"
#include "Logger.hpp"
#include "CubeMap.hpp"
#include "TerrainPrefab.hpp"

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
    chaos::CubeMap* loadResource(std::string fpath, const std::initializer_list<std::string>& listFileNames, std::string id){
        SHOUT("loading cubemap!\n");
        if(cache.find(id) != cache.end()){
            return dynamic_cast<chaos::CubeMap*>(cache[id]);
        }
        chaos::CubeMap* tmp = new chaos::CubeMap(fpath, textureLoader, listFileNames);
        cache[id] = tmp;
        return tmp;
    }
    chaos::TerrainPrefab* loadResource(chaos::Texture* heightmap, GLfloat minHeight, GLfloat maxHeight, GLfloat groundZeroHeightPercent, std::string id){
        SHOUT("loading terrain prefab!\n");
        if(cache.find(id) != cache.end()){
            return dynamic_cast<chaos::TerrainPrefab*>(cache[id]);
        }
        chaos::TerrainPrefab* tmp = new chaos::TerrainPrefab(heightmap, minHeight, maxHeight, groundZeroHeightPercent);
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
