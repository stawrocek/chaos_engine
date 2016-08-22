#ifndef DEBUG_CAMERA_HPP
#define DEBUG_CAMERA_HPP

#include "Gameobject.hpp"

namespace chaos {

enum CameraDirection {
    FORWARD, BACKWARD, LEFT, RIGHT
};

enum ProjectionMode{
    ORTHOGRAPHIC, PERSPECTIVE
};

class Camera: public GameObject
{
public:
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right;
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;
    float mvSpeed = 6.0f;
    float sens = 0.05f;

    Camera(std::string s, ProjectionMode m, glm::mat4 mx)
    :GameObject(s), projectionMode(m), mxProjection(mx)
    {
        update();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(getPosition(), getPosition() + front, up);
    }

    void processMouse(float xoff, float yoff) {
        xoff *= sens, yoff *= sens;
        yaw += xoff, pitch += yoff;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        update();
    }

    void processKeyboard(CameraDirection dir, float delta) {
        float vel = mvSpeed * delta;
        if(dir == FORWARD)  translate(vel*front);
        if(dir == BACKWARD) translate(-vel*front);
        if(dir == LEFT)     translate(-vel*right);
        if(dir == RIGHT)    translate(vel*right);
    }

    void update() {
        glm::vec3 frnt;
        frnt.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        frnt.y = sin(glm::radians(pitch));
        frnt.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(frnt);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    glm::mat4 getProjectionMatrix(){
        return mxProjection;
    }

    void setProjectionMatrix(glm::mat4 m){
        mxProjection = m;
    }

    ProjectionMode getProjectionMode(){
        return projectionMode;
    }

    void setProjectionMode(ProjectionMode m){
        projectionMode = m;
    }

private:
    ProjectionMode projectionMode;
    glm::mat4 mxProjection;

};

}

#endif //namespace chaos



