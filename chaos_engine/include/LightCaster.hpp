#ifndef LIGHTCASTER_HPP
#define LIGHTCASTER

#include "GameObject.hpp"

namespace chaos{

class Scene;

class CHAOS_EXPORT LightCaster: public GameObject{
public:
    LightCaster(Renderer* ren, Scene* scn);
    virtual void setupUniforms(chaos::ShaderProgram*shr, GameObject* obj, GLuint index)=0;

protected:
    Scene* scene;
};

class CHAOS_EXPORT PointLight: public LightCaster{
public:
    PointLight(Renderer* ren, Scene* scn);
    void setupUniforms(chaos::ShaderProgram*shr, GameObject* obj, GLuint index);
    void setAttenuationCoefficients(GLfloat constant, GLfloat linear, GLfloat quadratic);
    GLfloat getConstantAttenuationCoefficient();
    GLfloat getLinearAttenuationCoefficient();
    GLfloat getQuadraticAttenuationCoefficient();

protected:
    GLfloat constant=1.0, linear, quadratic;
};

}

#endif // LIGHTCASTER_HPP
