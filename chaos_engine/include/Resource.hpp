#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

namespace chaos{

class Resource{
public:
    Resource(std::string fpath){};
    virtual ~Resource(){};
};

}

#endif // RESOURCE_HPP
