#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "GameObject.hpp"
#include "CubeMap.hpp"
#include "ShaderProgram.hpp"
#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Camera.hpp"

namespace chaos{

class Skybox: public GameObject
{
public:
    Skybox()=delete;
    Skybox(Renderer* ren, CubeMap* cb);
    virtual ~Skybox();
    void setCubeMap(CubeMap*);
    CubeMap* getCubeMap();

    virtual void draw() override;


protected:
    CubeMap* cubeMap = nullptr;
};

}
#endif // SKYBOX_HPP
