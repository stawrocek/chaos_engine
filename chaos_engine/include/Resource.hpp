#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

#include "Export.hpp"
#include "Application.hpp"

namespace chaos{

class CHAOS_EXPORT Resource{
public:
    Resource(std::string& fpath);
    virtual ~Resource();
};

}

#endif // RESOURCE_HPP
