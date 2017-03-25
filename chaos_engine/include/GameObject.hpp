#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "Export.hpp"

#include "Transform.hpp"
#include "Material.hpp"

namespace chaos{

class Camera;
class Renderer;
class ShaderProgram;
class VertexArray;

class CHAOS_EXPORT GameObject: public Transform {
public:
    GameObject(Renderer* ren);
    GameObject(Renderer* ren, std::string vaoId, std::string shaderId);
    virtual ~GameObject();
    virtual void draw();
    void setVertexArray(std::string id);
    VertexArray* getVertexArray();
    void setShader(std::string id);
    ShaderProgram* getShader();
    glm::vec4 getColor();
    void setColor(glm::vec4 c);
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    Renderer* getRenderer();
    void setRenderer(Renderer* ren);
    virtual void drawGizmo(GLfloat scale=3.0f);
    virtual void setLightingEnabled(GLboolean enable);
    GLboolean isLightingEnabled();

    Material material;

protected:
    glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f);
    ShaderProgram* shader = nullptr;
    VertexArray* vao = nullptr;
    Renderer* renderer = nullptr;
    GLboolean isLighting=false;
};

}

#endif // GAME_OBJECT_HPP

