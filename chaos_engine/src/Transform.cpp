#include "../include/Transform.hpp"

using namespace chaos;

Transform::Transform()
:posX(0.f),posY(0.f),posZ(0.f),
scaleX(1.f),scaleY(1.f),scaleZ(1.f),
rotX(0.0f),rotY(0.0f),rotZ(0.0f)
{
    mxTransform = glm::mat4();
    parent = nullptr;
}

glm::mat4 Transform::getLocalTransformMatrix() {
    if(!needUpdate)
        return mxTransform;
    mxTransform = glm::mat4();
    mxTransform = glm::translate(mxTransform, glm::vec3(posX, posY, posZ));
    mxTransform = glm::scale(mxTransform, glm::vec3(scaleX, scaleY, scaleZ));
    glm::quat q(glm::vec3(rotX, rotY, rotZ));
    /*mxTransform = glm::rotate(mxTransform, rotX, getRight());
    mxTransform = glm::rotate(mxTransform, rotY, getUp());
    mxTransform = glm::rotate(mxTransform, rotZ, getFront());*/
    mxTransform = mxTransform*glm::toMat4(q);


    needUpdate=false;
    return mxTransform;
}

glm::mat4 Transform::getGlobalTransformMatrix() {
    glm::mat4 mx = getLocalTransformMatrix();
    if(parent == nullptr) {
        return getLocalTransformMatrix();
    }
    else {
        return parent->getGlobalTransformMatrix() * getLocalTransformMatrix();
    }
    return mx;
}

void Transform::translate(GLfloat dx, GLfloat dy, GLfloat dz) {
    posX += dx;
    posY += dy;
    posZ += dz;
    needUpdate=true;
}

void Transform::translate(glm::vec3 vec) {
    posX += vec.x;
    posY += vec.y;
    posZ += vec.z;
    needUpdate = true;
}

void Transform::rotate(GLfloat dx, GLfloat dy, GLfloat dz) {
    rotX += dx;
    rotY += dy;
    rotZ += dz;
    needUpdate=true;
}

void Transform::rotate(glm::vec3 vec) {
    rotX += vec.x;
    rotY += vec.y;
    rotZ += vec.z;
    needUpdate = true;
}

void Transform::scaleUp(GLfloat dx, GLfloat dy, GLfloat dz) {
    scaleX += dx;
    scaleY += dy;
    scaleZ += dz;
    needUpdate = true;
}

void Transform::scaleUp(glm::vec3 vec) {
    scaleX += vec.x;
    scaleY += vec.y;
    scaleZ += vec.z;
    needUpdate = true;
}

void Transform::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    posX = x;
    posY = y;
    posZ = z;
    needUpdate=true;
}

void Transform::setPosition(glm::vec3 vec) {
    posX = vec.x;
    posY = vec.y;
    posZ = vec.z;
    needUpdate = true;
}

void Transform::setRotation(GLfloat x, GLfloat y, GLfloat z) {
    rotX = x;
    rotY = y;
    rotZ = z;
    needUpdate = true;
}

void Transform::setRotation(glm::vec3 vec) {
    rotX = vec.x;
    rotY = vec.y;
    rotZ = vec.z;
    needUpdate = true;
}

void Transform::setScale(GLfloat dx, GLfloat dy, GLfloat dz) {
    scaleX = dx;
    scaleY = dy;
    scaleZ = dz;
    needUpdate=true;
}

void Transform::setScale(glm::vec3 vec) {
    scaleX = vec.x;
    scaleY = vec.y;
    scaleZ = vec.z;
    needUpdate=true;
}

void Transform::setParent(Transform* t) {
    parent = t;
    t->vecChildren.push_back(this);
}

glm::vec3 Transform::getFront(){
    glm::vec3 vFront(0,0,1);
    vFront = glm::rotate(vFront, rotX, glm::vec3(1,0,0));
    vFront = glm::rotate(vFront, rotY, glm::vec3(0,1,0));
    vFront = glm::rotate(vFront, rotZ, glm::vec3(0,0,1));
    return -glm::normalize(vFront);
}

glm::vec3 Transform::getRight(){
    glm::vec3 vRight(1,0,0);
    vRight = glm::rotate(vRight, rotX, glm::vec3(1,0,0));
    vRight = glm::rotate(vRight, rotY, glm::vec3(0,1,0));
    vRight = glm::rotate(vRight, rotZ, glm::vec3(0,0,1));
    return glm::normalize(vRight);
}

glm::vec3 Transform::getUp(){
    glm::vec3 vUp(0,1,0);
    vUp = glm::rotate(vUp, rotX, glm::vec3(1,0,0));
    vUp = glm::rotate(vUp, rotY, glm::vec3(0,1,0));
    vUp = glm::rotate(vUp, rotZ, glm::vec3(0,0,1));
    return glm::normalize(vUp);
}
