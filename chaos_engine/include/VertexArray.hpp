#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
#include <iostream>
#include <initializer_list>

namespace chaos{

struct VertexData{
    VertexData();
    VertexData(const std::initializer_list<GLfloat>& vV, const std::initializer_list<GLfloat>& vC,
               const std::initializer_list<GLfloat>& vU, const std::initializer_list<GLfloat>& vD);

    std::vector<GLfloat> vVerts;
    std::vector<GLfloat> vColor;
    std::vector<GLfloat> vUV;
    std::vector<GLfloat> vData;
};

class VertexArray
{
public:
    VertexArray(GLuint vertsSize, GLuint colorSize, GLuint uvSize, GLuint dataSize);
    VertexArray(GLuint vertsSize, GLuint colorSize, GLuint uvSize, GLuint dataSize, std::vector<GLfloat>* vec);
    virtual ~VertexArray();

    void addVertex(VertexData vd);
    void setVertices(GLuint id, const std::initializer_list<GLfloat>& v);
    void setColor(GLuint id, const std::initializer_list<GLfloat>& v);
    void setUV(GLuint id, const std::initializer_list<GLfloat>& v);
    void setData(GLuint id, const std::initializer_list<GLfloat>& v);
    void buildArrayOfPlainData(std::vector<GLfloat>* v);

    GLuint getId()          {return VAO;}
    GLuint getVboId()       {return VBO;}
    GLuint countVertices()  {return vVertices.size();}
    void generateVertexArray(GLenum target, GLenum usage);
    void bind();
    void unbind();

private:
    GLuint vertsSize;
    GLuint colorSize;
    GLuint uvSize;
    GLuint dataSize;

    std::vector<VertexData> vVertices;


    //opengl stuff
    GLuint VAO;
    GLuint VBO;
    GLenum target;
    GLenum usage;

};

}

#endif // VERTEXARRAY_HPP
