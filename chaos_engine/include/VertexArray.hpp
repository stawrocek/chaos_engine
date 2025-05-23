#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <vector>
#include <initializer_list>

#include "Export.hpp"

#include "Logger.hpp"

namespace chaos{

class ShaderProgram;

struct CHAOS_EXPORT VertexData{
    VertexData();
    VertexData(const std::initializer_list<GLfloat>& vV, const std::initializer_list<GLfloat>& vN,
               const std::initializer_list<GLfloat>& vU, const std::initializer_list<GLfloat>& vD);

    std::vector<GLfloat> vVerts;
    std::vector<GLfloat> vNormal;
    std::vector<GLfloat> vUV;
    std::vector<GLfloat> vData;
};

class CHAOS_EXPORT VertexArray
{
public:
    VertexArray(GLuint vertsSize, GLuint normalSize, GLuint uvSize, GLuint dataSize);
    VertexArray(GLuint vertsSize, GLuint normalSize, GLuint uvSize, GLuint dataSize, std::vector<GLfloat>* vec);
    virtual ~VertexArray();

    void addVertex(VertexData vd);
    void setVertices(GLuint id, const std::initializer_list<GLfloat>& v);
    void setNormal(GLuint id, const std::initializer_list<GLfloat>& v);
    void setUV(GLuint id, const std::initializer_list<GLfloat>& v);
    void setData(GLuint id, const std::initializer_list<GLfloat>& v);
    void buildArrayOfPlainData(std::vector<GLfloat>* v);

#ifdef VAO_ENABLED
    GLuint getId()          {return VAO;}
#endif
    GLuint getVboId()       {return VBO;}
    GLuint countVertices()  {return vVertices.size();}
    void generateVertexArray(GLenum target, GLenum usage);
    void bind();
    void draw(ShaderProgram* shr, GLenum type=GL_TRIANGLES, GLint start=0, GLsizei end=-1);
    void unbind();
    GLuint getVerticesSize(){
        return vertsSize;
    }
    GLuint getNormalsSize(){
        return normalSize;
    }
    GLuint getUVSize(){
        return uvSize;
    }
    GLuint getDataSize(){
        return dataSize;
    }

private:
    GLuint vertsSize;
    GLuint normalSize;
    GLuint uvSize;
    GLuint dataSize;

    std::vector<VertexData> vVertices;

#ifdef VAO_ENABLED
    GLuint VAO;
#endif
    GLuint VBO;
    GLenum target;
    GLenum usage;
};

}

#endif // VERTEXARRAY_HPP
