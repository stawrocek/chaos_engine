#include "../include/Texture.hpp"

using namespace chaos;

GLuint Texture::textureCounter = 0;

Texture::Texture(std::string fpath)
:Resource(fpath)
{
    const char* test =  FreeImage_GetVersion();
    int availableFormats = FreeImage_GetFIFCount();
    int pngOk =  FreeImage_FIFSupportsReading(FIF_PNG);
    #ifdef ANDROID
    LOGI("%s, %d, %d", test, availableFormats, pngOk);
    #else
    std::cout << test << ", " << availableFormats << ", " << pngOk << "\n";
    #endif
    std::ifstream file(fpath, std::ios::binary | std::ios::ate);
    int fileSize = file.tellg();
    if(!file){
        std::cout << "[error]: couldn't open " << fpath << "\n";
        #ifdef ANDROID
        LOGI("[error]: couldn't open %s", fpath.c_str());
        #endif // ANDROID
    }

    std::string textureStr = std::string((std::istreambuf_iterator<char>(file)),
    std::istreambuf_iterator<char>());
    #ifdef ANDROID
    LOGI("loading image: %s as %s, size=%d", fpath.c_str(), textureStr.c_str(), fileSize);
    #else
    std::cout << "loading image " << fpath << ", " << textureStr.c_str() << ", size=" << fileSize << "\n";
    #endif // ANDROID
    file.close();
    batchId = textureCounter;

    glGenTextures(1, &id);
    bind(GL_TEXTURE_2D);

    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(fpath.c_str(), 0);
    if(format == FIF_UNKNOWN) {
        #ifdef ANDROID
        LOGI("Failed to read format %s", fpath.c_str());
        #endif // ANDROID
        std::cout << "Failed to read format @ " << fpath.c_str() << "\n";
    }
    if(format == FIF_UNKNOWN) {
        #ifdef ANDROID
        LOGI("Failed to read format v2 %s", fpath.c_str());
        #endif // ANDROID
        std::cout << "Failed to read format v2 @ " << fpath.c_str() << "\n";
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
    #ifdef ANDROID
    LOGI("width: %d, height:%d", (int)width, (int)height);
    #endif
    textureData = FreeImage_GetBits(bitmap32);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,textureData);
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
