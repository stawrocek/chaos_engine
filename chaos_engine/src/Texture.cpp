#include "Texture.hpp"

using namespace chaos;

GLuint Texture::textureCounter = 0;

Texture::Texture(std::string fpath)
:Resource(fpath)
{
    batchId = textureCounter;

    glGenTextures(1, &id);
    bind(GL_TEXTURE_2D);

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fpath.c_str(), 0);
    if(format == -1) {
        std::cout << "Failed to read format @ " << fpath.c_str() << "\n";
    }

    FIBITMAP* bitmap = FreeImage_Load(format, fpath.c_str());
    FIBITMAP* bitmap32 = nullptr;

    int bpp = FreeImage_GetBPP(bitmap);
    if(bpp == 32)
        bitmap32 = bitmap;
    else
        bitmap32 = FreeImage_ConvertTo32Bits(bitmap);

    width = FreeImage_GetWidth(bitmap32);
    height = FreeImage_GetHeight(bitmap32);
    textureData = FreeImage_GetBits(bitmap32);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_BGRA,GL_UNSIGNED_BYTE,textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    FreeImage_Unload(bitmap32);
    if(bpp != 32) {
        FreeImage_Unload(bitmap);
    }

    unbind();
    textureCounter++;
}

Texture::~Texture(){
    std::cout << "Destructor of Texture\n";
    glDeleteTextures(1, &id);
}

void Texture::loadFromTextureData(Texture* data){

}

void Texture::bind(GLenum t) {
    type = t;
    glBindTexture(type, id);
}

void Texture::use(GLenum slot){
    glActiveTexture(slot);
    glBindTexture(type, id);
}

void Texture::unbind(){
    glBindTexture(type, 0);
}

GLenum Texture::getTextureType(){
    return type;
}

GLubyte* Texture::getTextureData(){
    return textureData;
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
