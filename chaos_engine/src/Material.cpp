#include "../include/Material.hpp"

chaos::Material::Material(glm::vec4 diffuse, glm::vec4 specular, GLuint _shininess)
:diffuseColor(diffuse), specularColor(specular), shininess(_shininess)
{}

void chaos::Material::setDiffuseColor(glm::vec4 diffuse){
    diffuseColor = diffuse;
}
void chaos::Material::setSpecularColor(glm::vec4 specular){
    specularColor = specular;
}

void chaos::Material::setShininess(GLfloat newShininess){
    shininess = newShininess;
}
glm::vec4 chaos::Material::getDiffuseColor(){
    return diffuseColor;
}

glm::vec4 chaos::Material::getSpecularColor(){
    return specularColor;
}

GLfloat chaos::Material::getShininess(){
    return shininess;
}
