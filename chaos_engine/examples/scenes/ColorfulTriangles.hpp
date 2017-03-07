#ifndef COLORFUL_TRIANGLES_HPP
#define COLORFUL_TRIANGLES_HPP

#include "../../include/Scene.hpp"

class ColorfulTriangles: public chaos::Scene{
public:
    ColorfulTriangles(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        vao = renderer->getVAO("Rectangle:Vao_Pos");
        shr = renderer->getShader("Shader_Pos");
        txTriangle = new chaos::Transform();
        txTriangle->setScale(0.1,0.1,0.1);
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        window->clearColor(0.2, 0.7, 0.2, 1.0);

        shr->run();
        shr->setUniform("uniColor", glm::vec4(1,0,0,1));
        shr->setUniform("mx", txTriangle->getGlobalTransformMatrix());
        vao->bind();
        vao->draw(shr);
        vao->unbind();
        glUseProgram(0);
    }

private:
    chaos::VertexArray* vao = nullptr;
    chaos::ShaderProgram* shr = nullptr;
    chaos::Transform* txTriangle = nullptr;

};

#endif // COLORFUL_TRIANGLES_HPP
