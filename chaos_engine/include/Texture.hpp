#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
#include <iostream>
#include <iostream>
#include <streambuf>
#include <fstream>
#include <vector>

#ifdef _WIN32
    #include "windows.h"
#endif

#include "Export.hpp"

#include "Resource.hpp"

/*#ifdef TEXTURES_FREEIMAGE
#include "../lib-loaders/FreeImageTextureLoader.hpp"

#else
#include "../lib-loaders/SDL_Texture_Loader.hpp"

#endif*/

namespace chaos{

class CHAOS_EXPORT TextureLoader{
public:
    TextureLoader(){};
    TextureLoader(const TextureLoader& that) = delete;
    TextureLoader(std::string fpath){};
    virtual void loadTexture(std::string fpath)=0;
    virtual GLuint getWidth(){
        return width;
    }
    virtual GLuint getHeight(){
        return height;
    }
    virtual GLubyte* getTextureData(){
        return textureData;
    }
    virtual glm::vec4 getColorsFromIndex(GLuint index){
        return glm::vec4(textureData[index], textureData[index+1], textureData[index+2], textureData[index+3]);
    }
    virtual GLboolean initializeTextureLoader() = 0;

protected:
    GLuint width, height;
    GLubyte* textureData;
};

class CHAOS_EXPORT Texture: public Resource
{
public:
    Texture(std::string fpath, TextureLoader* textureLoader);
    Texture(GLuint glId, GLuint w, GLuint h);
    virtual ~Texture();

    GLuint getWidth();
    GLuint getHeight();
    GLuint getId();
    GLuint getBatchId();
    GLenum getTextureType();
    void bind(GLenum type=GL_TEXTURE_2D);
    void bindOnSlot(GLenum slot=0, GLenum type=GL_TEXTURE_2D);
    void unbind();
    void unbindUnit();
    std::vector<std::vector<glm::vec4> > getTextureData() const;

protected:
    GLuint width;
    GLuint height;
    GLenum type=GL_TEXTURE_2D;
    GLuint id;                      //opengl id
    GLuint batchId;                 //batching id (different Texture => different batchId)
    static GLuint textureCounter;   //generates batchId
    std::vector<std::vector<glm::vec4> > vecTextureData;

};

}

#endif // TEXTURE_HPP
