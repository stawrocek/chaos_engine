#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "Export.hpp"
#include "GameObject.hpp"
#include "TerrainPrefab.hpp"
#include "Texture.hpp"

#include <vector>

namespace chaos{

class Terrain: public GameObject
{
public:
    enum TextureType{
        BLEND_MAP  = 0,
        BACKGROUND = 1,
        TEXTURE_R  = 2,
        TEXTURE_G  = 3,
        TEXTURE_B  = 4
    };

    Terrain(Renderer*, TerrainPrefab*, std::initializer_list<std::pair<TextureType, Texture*> > listTextures);
    virtual ~Terrain();
    virtual void draw();
    void setTerrainMesh(TerrainPrefab* prefab);
protected:
    TerrainPrefab* terrainPrefab = nullptr;
    //0->blend map
    //1->background
    //2->r
    //3->g
    //4->b
    //5->a (?) not supported for now
    std::vector<chaos::Texture*> vecTextures;
    const int textureTypesCount=5;
};

}

#endif // TERRAIN_HPP
