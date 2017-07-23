#include "../include/CubeMap.hpp"
#include "../include/ResourceManager.hpp"

chaos::CubeMap::CubeMap(std::string fpath, chaos::TextureLoader* textureLoader, const std::initializer_list<std::string>& listFileNames)
:Resource(fpath)
{
    glGenTextures(1, &id);
    bind();
    GLuint textureCounter=0;
    for (std::string fileName : listFileNames) {
        std::string filePath = getFilePath()+fileName;
        textureLoader->loadTexture(filePath);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + textureCounter,0,GL_RGBA,
                        textureLoader->getWidth(), textureLoader->getHeight(), 0, GL_RGBA,
                        GL_UNSIGNED_BYTE, textureLoader->getTextureData());
        textureCounter++;
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    #if !defined(ANDROID) && !defined(__EMSCRIPTEN__)
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    #endif
}

chaos::CubeMap::~CubeMap(){
    glDeleteTextures(1, &id);
}

void chaos::CubeMap::bind(){
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

GLuint chaos::CubeMap::getId(){
    return id;
}
