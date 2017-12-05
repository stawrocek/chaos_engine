#include "../include/Transform.hpp"

#include <iostream>


chaos::Transform::Transform()
:posX(0.f),posY(0.f),posZ(0.f),
scaleX(1.f),scaleY(1.f),scaleZ(1.f),
rotX(0.0f),rotY(0.0f),rotZ(0.0f),
keyX(0.0), keyY(0.0), keyZ(0.0)
{
    mxTransform = glm::mat4();
    parent = nullptr;
}

glm::mat4 chaos::Transform::getLocalTransformMatrix() {
    if(!needUpdate)
        return mxTransform;
    mxTransform = glm::mat4();
    mxTransform = glm::translate(mxTransform, glm::vec3(posX, posY, posZ));
    mxTransform = glm::scale(mxTransform, glm::vec3(scaleX, scaleY, scaleZ));
    glm::quat quatKey(glm::vec3(keyX, keyY, keyZ));
    keyX=keyY=keyZ=0.0f;
    quatStorage = quatKey*quatStorage;
    quatStorage = glm::normalize(quatStorage);
    needUpdate=false;
    mxTransform = mxTransform*glm::toMat4(quatStorage);
    return mxTransform;
}

glm::mat4 chaos::Transform::getGlobalTransformMatrix() {
    glm::mat4 mx = getLocalTransformMatrix();
    if(parent == nullptr) {
        return getLocalTransformMatrix();
    }
    else {
        return parent->getGlobalTransformMatrix() * getLocalTransformMatrix();
    }
    return mx;
}

void chaos::Transform::translate(GLfloat dx, GLfloat dy, GLfloat dz) {
    posX += dx;
    posY += dy;
    posZ += dz;
    needUpdate=true;
}

void chaos::Transform::translate(glm::vec3 vec) {
    posX += vec.x;
    posY += vec.y;
    posZ += vec.z;
    needUpdate = true;
}

void chaos::Transform::rotate(GLfloat dx, GLfloat dy, GLfloat dz) {
    keyX += dx;
    keyY += dy;
    keyZ += dz;

    rotX += dx;
    rotY += dy;
    rotZ += dz;
    needUpdate=true;
}

void chaos::Transform::rotate(glm::vec3 vec) {
    keyX += vec.x;
    keyY += vec.y;
    keyZ += vec.z;

    rotX += vec.x;
    rotY += vec.y;
    rotZ += vec.z;
    needUpdate = true;
}

void chaos::Transform::scaleUp(GLfloat dx, GLfloat dy, GLfloat dz) {
    scaleX += dx;
    scaleY += dy;
    scaleZ += dz;
    needUpdate = true;
}

void chaos::Transform::scaleUp(glm::vec3 vec) {
    scaleX += vec.x;
    scaleY += vec.y;
    scaleZ += vec.z;
    needUpdate = true;
}

void chaos::Transform::setPosition(GLfloat x, GLfloat y, GLfloat z) {
    posX = x;
    posY = y;
    posZ = z;
    needUpdate=true;
}

void chaos::Transform::setPosition(glm::vec3 vec) {
    posX = vec.x;
    posY = vec.y;
    posZ = vec.z;
    needUpdate = true;
}

void chaos::Transform::setRotation(GLfloat x, GLfloat y, GLfloat z) {
    keyX += x-rotX;
    keyY += y-rotY;
    keyZ += z-rotZ;

    rotX = x;
    rotY = y;
    rotZ = z;
    needUpdate = true;
}

void chaos::Transform::setRotation(glm::vec3 vec) {
    keyX += vec.x-rotX;
    keyY += vec.y-rotY;
    keyZ += vec.z-rotZ;

    rotX = vec.x;
    rotY = vec.y;
    rotZ = vec.z;
    needUpdate = true;
}

void chaos::Transform::setScale(GLfloat dx, GLfloat dy, GLfloat dz) {
    scaleX = dx;
    scaleY = dy;
    scaleZ = dz;
    needUpdate=true;
}

void chaos::Transform::setScale(glm::vec3 vec) {
    scaleX = vec.x;
    scaleY = vec.y;
    scaleZ = vec.z;
    needUpdate=true;
}

void chaos::Transform::setParent(Transform* t) {
    parent = t;
    t->vecChildren.push_back(this);
}

glm::vec3 chaos::Transform::getFront(){
    glm::vec3 vFront(0,0,1);
    vFront = glm::rotate(vFront, rotX, glm::vec3(1,0,0));
    vFront = glm::rotate(vFront, rotY, glm::vec3(0,1,0));
    vFront = glm::rotate(vFront, rotZ, glm::vec3(0,0,1));
    return -glm::normalize(vFront);
}

glm::vec3 chaos::Transform::getRight(){
    glm::vec3 vRight(1,0,0);
    vRight = glm::rotate(vRight, rotX, glm::vec3(1,0,0));
    vRight = glm::rotate(vRight, rotY, glm::vec3(0,1,0));
    vRight = glm::rotate(vRight, rotZ, glm::vec3(0,0,1));
    return glm::normalize(vRight);
}

glm::vec3 chaos::Transform::getUp(){
    glm::vec3 vUp(0,1,0);
    vUp = glm::rotate(vUp, rotX, glm::vec3(1,0,0));
    vUp = glm::rotate(vUp, rotY, glm::vec3(0,1,0));
    vUp = glm::rotate(vUp, rotZ, glm::vec3(0,0,1));
    return glm::normalize(vUp);
}

void chaos::Transform::rotateX(GLfloat dx){
    keyX += dx;
    rotX+=dx;needUpdate=true;
}

void chaos::Transform::rotateY(GLfloat dy){
    keyY += dy;
    rotY+=dy;needUpdate=true;
}

void chaos::Transform::rotateZ(GLfloat dz){
    keyZ += dz;
    rotZ+=dz;needUpdate=true;
}

void chaos::Transform::moveX(GLfloat dx){
    posX+=dx;needUpdate=true;
}

void chaos::Transform::moveY(GLfloat dy){
    posY+=dy;needUpdate=true;
}

void chaos::Transform::moveZ(GLfloat dz){
    posZ+=dz;needUpdate=true;
}

void chaos::Transform::scaleUpX(GLfloat dx){
    scaleX += dx; needUpdate=true;
}

void chaos::Transform::scaleUpY(GLfloat dy){
    scaleY += dy; needUpdate=true;
}

void chaos::Transform::scaleUpZ(GLfloat dz){
    scaleZ += dz; needUpdate=true;
}
/* -###- getters -###- */
GLfloat chaos::Transform::getX(){
    return posX;
}

GLfloat chaos::Transform::getY(){
    return posY;
}

GLfloat chaos::Transform::getZ(){
    return posZ;
}

GLfloat chaos::Transform::getScaleX(){
    return scaleX;
}

GLfloat chaos::Transform::getScaleY(){
    return scaleY;
}

GLfloat chaos::Transform::getScaleZ(){
    return scaleZ;
}

GLfloat chaos::Transform::getRotX(){
    return rotX;
}

GLfloat chaos::Transform::getRotY(){
    return rotY;
}

GLfloat chaos::Transform::getRotZ(){
    return rotZ;
}
/* -###- setters -###- */
void chaos::Transform::setX(GLfloat x){
    posX=x;needUpdate=true;
}

void chaos::Transform::setY(GLfloat y){
    posY=y;needUpdate=true;
}

void chaos::Transform::setZ(GLfloat z){
    posZ=z;needUpdate=true;
}

void chaos::Transform::setScaleX(GLfloat x){
    scaleX=x;needUpdate=true;
}

void chaos::Transform::setScaleY(GLfloat y){
    scaleY=y;needUpdate=true;
}

void chaos::Transform::setScaleZ(GLfloat z){
    scaleZ=z;needUpdate=true;
}

void chaos::Transform::setRotX(GLfloat x){
    keyX += x-rotX;
    rotX=x;
    needUpdate=true;
}

void chaos::Transform::setRotY(GLfloat y){
    keyY += y-rotY;
    rotY=y;
    needUpdate=true;
}

void chaos::Transform::setRotZ(GLfloat z){
    keyZ += z-rotZ;
    rotZ=z;
    needUpdate=true;
}

glm::vec3 chaos::Transform::getPosition(){
    return glm::vec3(posX,posY,posZ);
}

glm::vec3 chaos::Transform::getRotation(){
    return glm::vec3(rotX,rotY,rotZ);
}

glm::vec3 chaos::Transform::getScale()   {
    return glm::vec3(scaleX,scaleY,scaleX);
}

void chaos::Transform::print(){
    std::cout << glm::to_string(mxTransform) << "\n";
}

chaos::Transform* chaos::Transform::getParent(){
    return parent;
}
