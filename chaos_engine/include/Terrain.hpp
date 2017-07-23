#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Export.hpp"
#include "GameObject.hpp"
#include "TerrainPrefab.hpp"

namespace chaos{

class Terrain: public GameObject
{
public:
    Terrain(Renderer*, TerrainPrefab*);
    virtual ~Terrain();
    virtual void draw();
    void setTerrainMesh(TerrainPrefab* prefab);
protected:
    TerrainPrefab* terrainPrefab = nullptr;
};

}

#endif // TERRAIN_HPP
