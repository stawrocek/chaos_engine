#ifndef DEBUG_CAMERA_HPP
#define DEBUG_CAMERA_HPP

#include "Export.hpp"
#include "Gameobject.hpp"

namespace chaos {

enum CHAOS_EXPORT CameraDirection {
    FORWARD, BACKWARD, LEFT, RIGHT
};

enum CHAOS_EXPORT ProjectionMode{
    ORTHOGRAPHIC, PERSPECTIVE
};

class CHAOS_EXPORT Camera: public GameObject
{
public:
    float mvSpeed = 6.0f;
    float sens = 0.003f;

    Camera(Renderer* ren, ProjectionMode m, glm::mat4 mx)
    :GameObject(ren), projectionMode(m), mxProjection(mx)
    {}

    glm::mat4 getViewMatrix() {
        return glm::lookAt(getPosition(), getPosition() + getFront(), getUp());
    }

    void processMouse(float xoff, float yoff) {
        xoff *= sens, yoff *= sens;
        rotateY(-xoff);
        rotateX(yoff);

        if(getRotX() > M_PI/2.0-0.01)
            setRotX(M_PI/2.0-0.01);
        if(getRotX() < -M_PI/2.0+0.01)
            setRotX(M_PI/2.0+0.01);

    }

    void processKeyboard(CameraDirection dir, float delta) {
        float vel = mvSpeed * delta;
        if(dir == FORWARD)  translate(vel*getFront());
        if(dir == BACKWARD) translate(-vel*getFront());
        if(dir == LEFT)     translate(-vel*getRight());
        if(dir == RIGHT)    translate(vel*getRight());
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



