#include "../include/Texture.hpp"

using namespace chaos;

GLuint Texture::textureCounter = 0;

Texture::Texture(std::string fpath)
:Resource(fpath)
{
    batchId = textureCounter;
    glGenTextures(1, &id);
    bind(GL_TEXTURE_2D);

    TextureLoader textureLoader(fpath);
    width = textureLoader.width;
    height = textureLoader.height;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,textureLoader.textureData);

    unbind();
    textureCounter++;
}

Texture::~Texture(){
    glDeleteTextures(1, &id);
}

void Texture::bind(GLenum t) {
    type = t;
    glBindTexture(type, id);
}

/*void Texture::bindOnSlot(GLenum slot){
    glActiveTexture(slot);
    glBindTexture(type, id);
}*/

void Texture::unbind(){
    glBindTexture(type, 0);
}

GLenum Texture::getTextureType(){
    return type;
}

GLuint Texture::getWidth(){
    return width;
}

GLuint Texture::getHeight(){
    return height;
}

GLuint Texture::getId(){
    return id;
}

GLuint Texture::getBatchId(){
    return batchId;
}
