#ifndef WATER_HPP
#define WATER_HPP

#include "Export.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"

namespace chaos{

class Camera;
class FBO;

class CHAOS_EXPORT Water: public GameObject
{
public:
    Water(Renderer* ren, Camera* cam);
    virtual ~Water();
    FBO* getReflectionFBO();
    FBO* getRefractionFBO();
    void draw() override;
protected:
    FBO* reflectionFBO;
    FBO* refractionFBO;
    Camera* camera;
};

}
#endif // WATER_HPP
