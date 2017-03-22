#include "../include/Texture.hpp"

GLuint chaos::Texture::textureCounter = 0;

chaos::Texture::Texture(std::string fpath)
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

chaos::Texture::~Texture(){
    glDeleteTextures(1, &id);
}

void chaos::Texture::bind(GLenum t) {
    type = t;
    glBindTexture(type, id);
}

/*void Texture::bindOnSlot(GLenum slot){
    glActiveTexture(slot);
    glBindTexture(type, id);
}*/

void chaos::Texture::unbind(){
    glBindTexture(type, 0);
}

GLenum chaos::Texture::getTextureType(){
    return type;
}

GLuint chaos::Texture::getWidth(){
    return width;
}

GLuint chaos::Texture::getHeight(){
    return height;
}

GLuint chaos::Texture::getId(){
    return id;
}

GLuint chaos::Texture::getBatchId(){
    return batchId;
}
