#ifndef CUBEMAP_HPP
#define CUBEMAP_HPP

#include <string>
#include <initializer_list>
#include "Export.hpp"
#include "Texture.hpp"
#include "Resource.hpp"

namespace chaos{

class CHAOS_EXPORT CubeMap: public Resource
{
public:
    CubeMap(std::string fpath, TextureLoader* textureLoader, const std::initializer_list<std::string>& listFileNames);
    virtual ~CubeMap();

    GLuint getId();
    void bind();
    void unbind();

protected:
    GLuint id;
};

}

#endif // CUBEMAP_HPP
