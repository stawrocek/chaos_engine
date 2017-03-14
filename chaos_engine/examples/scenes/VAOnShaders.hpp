#ifndef VAONSHADERS_HPP
#define VAONSHADERS_HPP

#include "../../include/Scene.hpp"

class VAOnShaders: public chaos::Scene{
public:
    VAOnShaders(std::string _name)
    :Scene(_name)
    {}

    void onSceneLoadToMemory(){
        vao = renderer->getVAO("Rectangle:Vao_Pos");
        shr = renderer->getShader("Shader_Pos");
        txTriangle = new chaos::Transform();
    }

    void onSceneActivate(){

    }

    void draw(GLfloat deltaTime){
        window->clearColor(0.2, 0.7, 0.2, 1.0);

        if(scale>1.1){
            scaleSpeed=-1;
            scale=1.1;
        }
        if(scale<0.9){
            scaleSpeed=1;
            scale=0.9;
        }
        scale += (GLfloat)scaleSpeed*0.001;
        txTriangle->setScale(scale*0.1, scale*0.1, scale*0.1);

        shr->run();
        shr->setUniform("uniColor", glm::vec4(1,scale-0.1,0,1));
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

    GLfloat scale=1.0;
    GLint scaleSpeed=1;

};

#endif // VAONSHADERS_HPP

