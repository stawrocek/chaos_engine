#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Export.hpp"

#include <string>
#include <iostream>
#include <iostream>
#include <streambuf>
#include <fstream>
#include <FreeImage.h>

#include "Resource.hpp"

namespace chaos{

class CHAOS_EXPORT Texture: public Resource
{
public:
    Texture(std::string fpath);
    virtual ~Texture();

    GLubyte* getTextureData();
    GLuint getWidth();
    GLuint getHeight();
    GLuint getId();
    GLuint getBatchId();
    GLenum getTextureType();
    void loadFromTextureData(Texture* txtData);
    void bind(GLenum type=GL_TEXTURE_2D);
    //void bindOnSlot(GLenum slot);
    void unbind();

private:
    GLubyte* textureData;
    GLuint width;
    GLuint height;
    GLenum type=GL_TEXTURE_2D;
    GLuint id;                      //opengl id
    GLuint batchId;                 //batching id (different Texture => different batchId)
    static GLuint textureCounter;   //generates batchId

};

}

#endif // TEXTURE_HPP
