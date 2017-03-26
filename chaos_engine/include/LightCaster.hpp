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
        SpotLight = 2
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

protected:
    Scene* scene;
    LightType lightType;
    GLfloat diffuseStrength=1.0;
    GLfloat specularStrength=1.0;
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

}

#endif // LIGHTCASTER_HPP
