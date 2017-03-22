#ifndef DEBUG_CAMERA_HPP
#define DEBUG_CAMERA_HPP

#include "Export.hpp"
#include "Gameobject.hpp"

#define PI 3.14159265

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

    Camera(Renderer* ren, ProjectionMode m, glm::mat4 mx);
    glm::mat4 getViewMatrix();
    void processMouse(float xoff, float yoff);
    void processKeyboard(CameraDirection dir, float delta);
    glm::mat4 getProjectionMatrix();
    void setProjectionMatrix(glm::mat4 m);
    ProjectionMode getProjectionMode();
    void setProjectionMode(ProjectionMode m);

private:
    ProjectionMode projectionMode;
    glm::mat4 mxProjection;

};

}

#endif //namespace chaos



