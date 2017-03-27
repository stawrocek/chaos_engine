#ifndef MODEL_HPP
#define MODEL_HPP

#include "Export.hpp"

#include <string>
#include <fstream>

#include "GameObject.hpp"
#include "MeshPrefab.hpp"

namespace chaos
{

class Renderer;
class MeshPrefab;

class CHAOS_EXPORT Model: public GameObject{
public:
    Model(Renderer*r, MeshPrefab* prefab);
    virtual void draw();
    void setMesh(MeshPrefab* prefab);
    virtual void setLightingEnabled(GLboolean enable);

protected:
    MeshPrefab* meshPrefab = nullptr;
};


}

#endif //MODEL_HPP



