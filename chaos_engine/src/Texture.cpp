#include "../include/Texture.hpp"

GLuint chaos::Texture::textureCounter = 0;

chaos::Texture::Texture(std::string fpath, TextureLoader* textureLoader)
:Resource(fpath)
{
    batchId = textureCounter;
    glGenTextures(1, &id);
    bind(GL_TEXTURE_2D);

    textureLoader->loadTexture(getFilePath());
    width = textureLoader->getWidth();
    height = textureLoader->getHeight();
    vecTextureData.resize(height);
    GLuint ctr=0;
    for(GLuint i = 0; i < height; i++){
        vecTextureData[(height-1)-i].resize(width);
        for(GLuint j = 0; j < width; j++){
            vecTextureData[(height-1)-i][j] = textureLoader->getColorsFromIndex(ctr);
            ctr += 4;
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,textureLoader->getTextureData());
    unbind();
    textureCounter++;
}

chaos::Texture::Texture(GLuint glId, GLuint w, GLuint h)
{
    width=w;
    height=h;
    id = glId;
    batchId = textureCounter++;
}

chaos::Texture::~Texture(){
    glDeleteTextures(1, &id);
}

void chaos::Texture::bind(GLenum t) {
    type = t;
    glBindTexture(type, id);
}

void chaos::Texture::bindOnSlot(GLenum slot, GLenum t){
    glActiveTexture(slot);
    type=t;
    glBindTexture(type, id);
}

void chaos::Texture::unbind(){
    glBindTexture(type, 0);
}

void chaos::Texture::unbindUnit(){
    glActiveTexture(GL_TEXTURE0);
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

std::vector<std::vector<glm::vec4> > chaos::Texture::getTextureData() const {
    return vecTextureData;
}

