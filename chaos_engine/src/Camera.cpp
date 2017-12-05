#include "../include/Camera.hpp"

chaos::Camera::Camera(Renderer* ren, ProjectionMode m, glm::mat4 mx)
:GameObject(ren), projectionMode(m), mxProjection(mx)
{}

glm::mat4 chaos::Camera::getViewMatrix() {
    return glm::lookAt(getPosition(), getPosition() + getFront(), getUp());
}

void chaos::Camera::processMouse(float xoff, float yoff) {
    xoff *= sens, yoff *= sens;
    rotateY(-xoff);
    rotateX(yoff);

    rotateY(-xoff);
    if(getRotX() + yoff < PI/2.0 && getRotX() + yoff > -PI/2.0)
        rotateX(yoff);
}

void chaos::Camera::processKeyboard(CameraDirection dir, float delta) {
    float vel = mvSpeed * delta;
    if(dir == FORWARD)  translate(vel*getFront());
    if(dir == BACKWARD) translate(-vel*getFront());
    if(dir == LEFT)     translate(-vel*getRight());
    if(dir == RIGHT)    translate(vel*getRight());
}

glm::mat4 chaos::Camera::getProjectionMatrix(){
    return mxProjection;
}

void chaos::Camera::setProjectionMatrix(glm::mat4 m){
    mxProjection = m;
}

chaos::ProjectionMode chaos::Camera::getProjectionMode(){
    return projectionMode;
}

void chaos::Camera::setProjectionMode(ProjectionMode m){
    projectionMode = m;
}

void chaos::Camera::invertPitch(){
    setRotX(-getRotX());
}
