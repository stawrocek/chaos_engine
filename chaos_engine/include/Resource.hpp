#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "Export.hpp"

#include <string>

namespace chaos{

class CHAOS_EXPORT Resource{
public:
    Resource(std::string fpath){};
    virtual ~Resource(){};
};

}

#endif // RESOURCE_HPP
