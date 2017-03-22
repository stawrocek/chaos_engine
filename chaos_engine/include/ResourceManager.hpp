#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <unordered_map>
#include <string>
#include <iostream>

#include "Export.hpp"
#include "Resource.hpp"

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
private:
    std::unordered_map<std::string, Resource*> cache;

};

}
#endif // RESOURCEMANAGER_HPP
