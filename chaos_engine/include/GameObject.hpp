#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "Export.hpp"

#include "Transform.hpp"
#include "Renderer.hpp"
#include <ShaderProgram.hpp>

namespace chaos{

class CHAOS_EXPORT GameObject: public Transform{
public:
    GameObject(Renderer* ren)
    :renderer(ren)
    {}

    virtual ~GameObject(){}

    virtual void draw(){

    }

    Renderer* getRenderer(){
        return renderer;
    }

    void setRenderer(Renderer* ren){
        renderer = ren;
    }

protected:
    Renderer* renderer;
};

class CHAOS_EXPORT DrawableGameObject: public GameObject{
public:
    DrawableGameObject(Renderer* ren)
    :GameObject(ren)
    {}
    DrawableGameObject(Renderer* ren, std::string vaoId, std::string shaderId)
    :GameObject(ren)
    {
        setVertexArray(vaoId);
        setShader(shaderId);
    }
    virtual ~DrawableGameObject(){}
    virtual void draw(){
        shader->run();
        shader->setUniform("uniColor", color);
        shader->setUniform("mx",renderer->getCamCombined()*getGlobalTransformMatrix());

        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, vao->countVertices());
        vao->unbind();
    }
    void setVertexArray(std::string id){
        vao = renderer->getVAO(id);
    }
    VertexArray* getVertexArray(){
        return vao;
    }
    void setShader(std::string id){
        shader = renderer->getShader(id);
    }
    ShaderProgram* getShader(){
        return shader;
    }

    glm::vec4 getColor(){
        return color;
    }
    void setColor(glm::vec4 c){
        color = c;
    }

    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
        color = glm::vec4(r, g, b, a);
    }

protected:
    glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    ShaderProgram* shader = nullptr;
    VertexArray* vao = nullptr;
};

}

#endif // GAME_OBJECT_HPP

