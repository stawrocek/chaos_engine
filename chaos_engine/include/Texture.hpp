#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <iostream>
#include <streambuf>
#include <fstream>

#include "Export.hpp"

#include "Resource.hpp"

#ifdef TEXTURES_FREEIMAGE
#include "../lib-loaders/FreeImageTextureLoader.hpp"

#else
#include "../lib-loaders/SDL_Texture_Loader.hpp"

#endif

namespace chaos{

class CHAOS_EXPORT Texture: public Resource
{
public:
    Texture(std::string fpath);
    virtual ~Texture();

    GLuint getWidth();
    GLuint getHeight();
    GLuint getId();
    GLuint getBatchId();
    GLenum getTextureType();
    void bind(GLenum type=GL_TEXTURE_2D);
    //void bindOnSlot(GLenum slot);
    void unbind();

private:
    GLuint width;
    GLuint height;
    GLenum type=GL_TEXTURE_2D;
    GLuint id;                      //opengl id
    GLuint batchId;                 //batching id (different Texture => different batchId)
    static GLuint textureCounter;   //generates batchId

};

}

#endif // TEXTURE_HPP
