#ifndef LIGHTCASTER_HPP
#define LIGHTCASTER

#include "GameObject.hpp"

namespace chaos{

class Scene;

class CHAOS_EXPORT LightCaster: public GameObject{
public:
    enum LightType{
        PointLight = 0,
        DirectionalLight = 1,
        Spotlight = 2
    };

    LightCaster(Renderer*) = delete;
    LightCaster(Renderer* ren, Scene* scn, LightType lt);
    virtual void setupUniforms(chaos::ShaderProgram*shr, GameObject* obj, GLuint index)=0;
    LightType getLightType();
    void setLightType(LightType lt);
    void setDiffuseStrength(GLfloat diffStr);
    GLfloat getDiffuseStrength();
    void setSpecularStrength(GLfloat specStr);
    GLfloat getSpecularStrength();
    void setEnabled(GLboolean newValue);
    GLboolean isEnabled();

protected:
    Scene* scene;
    LightType lightType;
    GLfloat diffuseStrength=1.0;
    GLfloat specularStrength=1.0;
    GLboolean isLightEnabled=true;
};

class CHAOS_EXPORT PointLight: public LightCaster{
public:
    PointLight(Renderer* ren, Scene* scn);
    void setupUniforms(ShaderProgram* shr, GameObject* obj, GLuint index);
    void setAttenuationCoefficients(GLfloat constant, GLfloat linear, GLfloat quadratic);
    GLfloat getConstantAttenuationCoefficient();
    GLfloat getLinearAttenuationCoefficient();
    GLfloat getQuadraticAttenuationCoefficient();

protected:
    GLfloat constant=1.0, linear=0.09, quadratic=0.032;
};

class CHAOS_EXPORT DirectionalLight: public LightCaster{
public:
    DirectionalLight(Renderer* ren, Scene* scn);
    void setupUniforms(ShaderProgram* shr, GameObject* obj, GLuint index);
    void setDirection(glm::vec3 dir);
    glm::vec3 getDirection();

protected:
    glm::vec3 direction;
};

class CHAOS_EXPORT Spotlight: public LightCaster{
public:
    Spotlight(Renderer* ren, Scene* scn);
    void setupUniforms(ShaderProgram* shr, GameObject* obj, GLuint index);
    void setDirection(glm::vec3 dir);
    glm::vec3 getDirection();
    void setCutOffCosine(GLfloat newCosine);
    GLfloat getCutOffCosine();
    void setAttenuationCoefficients(GLfloat constant, GLfloat linear, GLfloat quadratic);
    GLfloat getConstantAttenuationCoefficient();
    GLfloat getLinearAttenuationCoefficient();
    GLfloat getQuadraticAttenuationCoefficient();

protected:
    GLfloat constant=1.0, linear=0.09, quadratic=0.032;
    glm::vec3 direction;
    GLfloat cutOffCosine=0.5;
};

}

#endif // LIGHTCASTER_HPP
