#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Export.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/string_cast.hpp"
//#include "header_only/ObjectData.hpp"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include <vector>
#include <iostream>

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

    void rotateX(GLfloat dx){rotX+=dx;needUpdate=true;}
    void rotateY(GLfloat dy){rotY+=dy;needUpdate=true;}
    void rotateZ(GLfloat dz){rotZ+=dz;needUpdate=true;}
    void moveX(GLfloat dx){posX+=dx;needUpdate=true;}
    void moveY(GLfloat dy){posY+=dy;needUpdate=true;}
    void moveZ(GLfloat dz){posZ+=dz;needUpdate=true;}
    void scaleUpX(GLfloat dx){scaleX += dx; needUpdate=true;}
    void scaleUpY(GLfloat dy){scaleY += dy; needUpdate=true;}
    void scaleUpZ(GLfloat dz){scaleZ += dz; needUpdate=true;}
    /* -###- getters -###- */
    GLfloat getX(){return posX;}
    GLfloat getY(){return posY;}
    GLfloat getZ(){return posZ;}
    GLfloat getScaleX(){return scaleX;}
    GLfloat getScaleY(){return scaleY;}
    GLfloat getScaleZ(){return scaleZ;}
    GLfloat getRotX(){return rotX;}
    GLfloat getRotY(){return rotY;}
    GLfloat getRotZ(){return rotZ;}
    /* -###- setters -###- */
    void setX(GLfloat x){posX=x;needUpdate=true;}
    void setY(GLfloat y){posY=y;needUpdate=true;}
    void setZ(GLfloat z){posZ=z;needUpdate=true;}
    void setScaleX(GLfloat x){scaleX=x;needUpdate=true;}
    void setScaleY(GLfloat y){scaleY=y;needUpdate=true;}
    void setScaleZ(GLfloat z){scaleZ=z;needUpdate=true;}
    void setRotX(GLfloat x){rotX=x;needUpdate=true;}
    void setRotY(GLfloat y){rotY=y;needUpdate=true;}
    void setRotZ(GLfloat z){rotZ=z;needUpdate=true;}

    glm::vec3 getPosition(){return glm::vec3(posX,posY,posZ);}
    glm::vec3 getRotation(){return glm::vec3(rotX,rotY,rotZ);}
    glm::vec3 getScale()   {return glm::vec3(scaleX,scaleY,scaleX);}

    glm::vec3 getFront();   //z
    glm::vec3 getRight();   //x
    glm::vec3 getUp();      //y

    void print(){
        std::cout << glm::to_string(mxTransform) << "\n";
    }

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

