#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

#include "Export.hpp"
#include "Application.hpp"

namespace chaos{

class CHAOS_EXPORT Resource{
public:
    Resource();
    Resource(std::string fpath);       //must be via reference
    virtual ~Resource();
    std::string getFilePath();
protected:
    std::string fpathDeviceDependent;
};

}

#endif // RESOURCE_HPP
