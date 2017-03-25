#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Export.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace chaos{

class CHAOS_EXPORT Material{
public:
    Material(glm::vec4 diffuse, glm::vec4 specular, GLuint shininess);
    void setDiffuseColor(glm::vec4);
    void setSpecularColor(glm::vec4);
    void setShininess(GLfloat);
    glm::vec4 getDiffuseColor();
    glm::vec4 getSpecularColor();
    GLfloat getShininess();


protected:
    glm::vec4 diffuseColor;
    glm::vec4 specularColor;
    GLfloat shininess;
};

}

#endif // MATERIAL_HPP
