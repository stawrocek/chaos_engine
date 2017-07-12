#ifndef FBO_HPP
#define FBO_HPP

#include "Export.hpp"
#include "Texture.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>

namespace chaos{

class CHAOS_EXPORT FBO
{
public:
    FBO()=delete;
    FBO(GLuint w, GLuint h, GLuint textureBufferCount=1,
        std::initializer_list<std::pair<GLenum,GLenum> > rboList={});
    virtual ~FBO();

    GLuint getId();
    void bind();
    void unbind();
    GLuint getWidth();
    GLuint getHeight();
    GLuint getTexturesCount();
    Texture* getTexture(GLuint index);
    GLuint getRBOCount();
    GLuint getRBO(GLuint index);

protected:
    GLuint id;
    GLuint width, height;
    std::vector<Texture*> vecTextures;
    std::vector<GLuint> vecRBO; //simple for now
};

}
#endif // FBO_HPP
