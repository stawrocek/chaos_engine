#include "../include/FBO.hpp"

chaos::FBO::FBO(GLuint w, GLuint h, GLuint textureBuffersCount,
                std::initializer_list<std::pair<GLenum,GLenum> > rboList)
:width(w), height(h)
{
    for(GLuint i = 0; i < vecTextures.size(); i++)
        delete vecTextures[i];
    vecRBO.clear();
    vecTextures.clear();

    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    for(GLuint i = 0; i < textureBuffersCount; i++){
        GLuint textureId;
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i, GL_TEXTURE_2D, textureId, 0);
        vecTextures.push_back(new chaos::Texture(textureId, width, height));
    }

    for(auto rboIt: rboList){
        GLuint rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, rboIt.first, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, rboIt.second, GL_RENDERBUFFER, rbo);
        vecRBO.push_back(rbo);
    }

    /*if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
    }
    else{
    }*/
    unbind();
}
chaos::FBO::~FBO(){
    glDeleteFramebuffers(1, &id);
}
GLuint chaos::FBO::getId(){
    return id;
}

void chaos::FBO::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void chaos::FBO::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint chaos::FBO::getWidth(){
    return width;
}

GLuint chaos::FBO::getHeight(){
    return height;
}

GLuint chaos::FBO::getTexturesCount(){
    return vecTextures.size();
}
chaos::Texture* chaos::FBO::getTexture(GLuint index){
    return vecTextures[index];
}

GLuint chaos::FBO::getRBOCount(){
    return vecRBO.size();
}
GLuint chaos::FBO::getRBO(GLuint index){
    return vecRBO[index];
}
