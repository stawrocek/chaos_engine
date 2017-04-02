#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vector>

#include "Export.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/string_cast.hpp"

//#include "header_only/ObjectData.hpp"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

namespace chaos {

/*
    Axis x -> from left(-) to right(+)
    Axis y -> from bottom(-) to top(+)
    Axis z -> from to user(-) to screen(+)
*/

enum Space{
    LOCAL = 1,
    GLOBAL = 2
};

class CHAOS_EXPORT Transform
{
public:
    Transform();

    /*get transform in local space*/
    glm::mat4 getLocalTransformMatrix();
    /*get transform in global space (scene)*/
    glm::mat4 getGlobalTransformMatrix();

    void setParent(Transform* t);

    void setPosition(GLfloat x, GLfloat y, GLfloat z=0.f);
    void setPosition(glm::vec3);
    void setRotation(GLfloat x, GLfloat y, GLfloat z);
    void setRotation(glm::vec3);
    void setScale(GLfloat dx, GLfloat dy, GLfloat dz=1.0f);
    void setScale(glm::vec3);

    /* -###- move by d -###- */
    void translate(GLfloat dx, GLfloat dy, GLfloat dz=0.f);
    void translate(glm::vec3);
    void rotate(GLfloat dx, GLfloat dy, GLfloat dz=0.f);
    void rotate(glm::vec3);
    void scaleUp(GLfloat dx, GLfloat dy, GLfloat dz=0.f);
    void scaleUp(glm::vec3);

    void rotateX(GLfloat dx);
    void rotateY(GLfloat dy);
    void rotateZ(GLfloat dz);
    void moveX(GLfloat dx);
    void moveY(GLfloat dy);
    void moveZ(GLfloat dz);
    void scaleUpX(GLfloat dx);
    void scaleUpY(GLfloat dy);
    void scaleUpZ(GLfloat dz);
    /* -###- getters -###- */
    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();
    GLfloat getScaleX();
    GLfloat getScaleY();
    GLfloat getScaleZ();
    GLfloat getRotX();
    GLfloat getRotY();
    GLfloat getRotZ();
    /* -###- setters -###- */
    void setX(GLfloat x);
    void setY(GLfloat y);
    void setZ(GLfloat z);
    void setScaleX(GLfloat x);
    void setScaleY(GLfloat y);
    void setScaleZ(GLfloat z);
    void setRotX(GLfloat x);
    void setRotY(GLfloat y);
    void setRotZ(GLfloat z);

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();

    glm::vec3 getFront();   //z
    glm::vec3 getRight();   //x
    glm::vec3 getUp();      //y

    Transform* getParent();

    void print();

protected:
    glm::mat4 mxTransform;
    bool needUpdate=false;
    GLfloat posX, posY, posZ;
    GLfloat scaleX, scaleY, scaleZ;
    GLfloat rotX, rotY, rotZ;
    glm::quat rotQuat;
    Transform* parent;
    std::vector<Transform* > vecChildren;
};

}
#endif // TRANSFORM_HPP

