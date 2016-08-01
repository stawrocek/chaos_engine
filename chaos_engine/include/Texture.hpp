#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <iostream>
#include <FreeImage.h>

namespace chaos{

class Texture
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
    void bind(GLenum type);
    void use(GLenum slot);
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
