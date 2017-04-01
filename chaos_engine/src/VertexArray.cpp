#include <iostream>

#include "../include/VertexArray.hpp"
#include "../include/ShaderProgram.hpp"
#include "../include/Logger.hpp"

chaos::VertexData::VertexData(){}

chaos::VertexData::VertexData(const std::initializer_list<GLfloat>& vV, const std::initializer_list<GLfloat>& vN,
             const std::initializer_list<GLfloat>& vU, const std::initializer_list<GLfloat>& vD)
{
    for(GLfloat x: vV)vVerts.push_back(x);
    for(GLfloat x: vN)vNormal.push_back(x);
    for(GLfloat x: vU)vUV.push_back(x);
    for(GLfloat x: vD)vData.push_back(x);
}

chaos::VertexArray::VertexArray(GLuint _vertsSize, GLuint _normalSize, GLuint _uvSize, GLuint _dataSize, std::vector<GLfloat>* vec)
:vertsSize(_vertsSize), normalSize(_normalSize), uvSize(_uvSize), dataSize(_dataSize)
{
    GLuint totalSize = vertsSize + normalSize + uvSize + dataSize;
    GLuint ctr=0;
    for(GLuint i = 0; i < vec->size()/totalSize; i++){
        VertexData vd;
        for(GLuint j = 0; j < vertsSize; j++){
            vd.vVerts.push_back(vec->at(ctr++));
        }
        for(GLuint j = 0; j < normalSize; j++){
            vd.vNormal.push_back(vec->at(ctr++));
        }
        for(GLuint j = 0; j < uvSize; j++){
            vd.vUV.push_back(vec->at(ctr++));
        }
        for(GLuint j = 0; j < dataSize; j++){
            vd.vData.push_back(vec->at(ctr++));
        }
        addVertex(vd);
    }
    std::vector<GLfloat> vData;
    buildArrayOfPlainData(&vData);
    generateVertexArray(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    unbind();
}

chaos::VertexArray::VertexArray(GLuint _vertsSize, GLuint _normalSize, GLuint _uvSize, GLuint _dataSize)
:vertsSize(_vertsSize), normalSize(_normalSize), uvSize(_uvSize), dataSize(_dataSize)
{

}

chaos::VertexArray::~VertexArray(){
    glDeleteBuffers(1, &VBO);
#ifdef VAO_ENABLED
    glDeleteVertexArrays(1, &VAO);
#endif
}

void chaos::VertexArray::addVertex(VertexData vd){
    vVertices.push_back(vd);
}
void chaos::VertexArray::setVertices(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vVerts.clear();
    for(GLfloat x: v){
        vVertices[id].vVerts.push_back(x);
    }
}
void chaos::VertexArray::setNormal(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vNormal.clear();
    for(GLfloat x: v){
        vVertices[id].vNormal.push_back(x);
    }
}
void chaos::VertexArray::setUV(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vUV.clear();
    for(GLfloat x: v){
        vVertices[id].vUV.push_back(x);
    }
}
void chaos::VertexArray::setData(GLuint id, const std::initializer_list<GLfloat>& v){
    vVertices[id].vData.clear();
    for(GLfloat x: v){
        vVertices[id].vData.push_back(x);
    }
}
void chaos::VertexArray::buildArrayOfPlainData(std::vector<GLfloat>* v){
    v->clear();
    for(GLuint i = 0; i < vVertices.size(); i++){
        for(GLuint j = 0; j < vertsSize; j++)
            v->push_back(vVertices[i].vVerts[j]);
        for(GLuint j = 0; j < normalSize; j++)
            v->push_back(vVertices[i].vNormal[j]);
        for(GLuint j = 0; j < uvSize; j++)
            v->push_back(vVertices[i].vUV[j]);
        for(GLuint j = 0; j < dataSize; j++)
            v->push_back(vVertices[i].vData[j]);
    }
}

void chaos::VertexArray::generateVertexArray(GLenum _target, GLenum _usage){
    std::vector<GLfloat> vxData;
    buildArrayOfPlainData(&vxData);
    target = _target;
    usage = _usage;

#ifdef VAO_ENABLED
    glGenVertexArrays(1, &VAO);
#endif
    glGenBuffers(1, &VBO);

#ifdef VAO_ENABLED
    glBindVertexArray(VAO);
#endif
    glBindBuffer(target, VBO);
    glBufferData(target, vxData.size()*sizeof(GLfloat), vxData.data(), usage);

    GLuint stride = vertsSize+normalSize+uvSize+dataSize;

#ifdef LAYOUT_LOCATION
    if(vertsSize != 0){
        glVertexAttribPointer(0, vertsSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    }
    if(normalSize != 0){
        glVertexAttribPointer(1, normalSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize)));
        glEnableVertexAttribArray(1);
    }
    if(uvSize != 0){
        glVertexAttribPointer(2, uvSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize)));
        glEnableVertexAttribArray(2);
    }
    if(dataSize != 0){
        glVertexAttribPointer(3, dataSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize+uvSize)));
        glEnableVertexAttribArray(3);
    }
#else
    GLuint attribCtr=0;
    if(vertsSize != 0){
        glVertexAttribPointer(attribCtr, vertsSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(attribCtr);
        attribCtr++;
    }
    if(normalSize != 0){
        glVertexAttribPointer(attribCtr, normalSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize)));
        glEnableVertexAttribArray(attribCtr);
        attribCtr++;
    }
    if(uvSize != 0){
        glVertexAttribPointer(attribCtr, uvSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize)));
        glEnableVertexAttribArray(attribCtr);
        attribCtr++;
    }
    if(dataSize != 0){
        glVertexAttribPointer(attribCtr, dataSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                              (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize+uvSize)));
        glEnableVertexAttribArray(attribCtr);
        attribCtr++;
    }

#endif

#ifdef VAO_ENABLED
    glBindVertexArray(0);
#else
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif // VAO_ENABLED
}

void chaos::VertexArray::bind(){
#ifdef VAO_ENABLED
    glBindVertexArray(VAO);
#else
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
#endif // VAO_ENABLED
}

void chaos::VertexArray::draw(chaos::ShaderProgram* shr, GLenum type, GLint start, GLsizei end){
    if(end==-1)
        end = countVertices();
    #ifdef VAO_ENABLED
        glDrawArrays(type, start, end);
    #else
        GLuint stride = vertsSize+normalSize+uvSize+dataSize;
        if(vertsSize != 0){
            GLint vertsLoc = glGetAttribLocation(shr->getId(), "position");
            glVertexAttribPointer(vertsLoc, vertsSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(vertsLoc);
        }
        if(normalSize != 0){
            GLint normalsLoc = glGetAttribLocation(shr->getId(), "normals");
            glVertexAttribPointer(normalsLoc, normalSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                                  (GLvoid*)(sizeof(GLfloat)*(vertsSize)));
            glEnableVertexAttribArray(normalsLoc);
        }
        if(uvSize != 0){
            GLint uvLoc = glGetAttribLocation(shr->getId(), "uv");
            glVertexAttribPointer(uvLoc, uvSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                                  (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize)));
            glEnableVertexAttribArray(uvLoc);
        }
        if(dataSize != 0){
            GLint dataLoc = glGetAttribLocation(shr->getId(), "data");
            glVertexAttribPointer(dataLoc, dataSize, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat),
                                  (GLvoid*)(sizeof(GLfloat)*(vertsSize+normalSize+uvSize)));
            glEnableVertexAttribArray(dataLoc);
        }
        glDrawArrays(type, start, end);
    #endif // VAO_ENABLED
}

void chaos::VertexArray::unbind(){
#ifdef VAO_ENABLED
    glBindVertexArray(0);
#else
    glBindBuffer(GL_ARRAY_BUFFER,0);
#endif
}
