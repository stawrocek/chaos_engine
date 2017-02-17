#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "Export.hpp"
#include "Application.hpp"
#include <string>

namespace chaos{

class CHAOS_EXPORT Resource{
public:
    Resource(std::string& fpath){
        fpath = chaos::Application::getDataStorageDirectory()+fpath;
    };
    virtual ~Resource(){};
};

}

#endif // RESOURCE_HPP
