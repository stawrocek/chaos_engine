#ifndef TERRAINPREFAB_HPP
#define TERRAINPREFAB_HPP

#include "Export.hpp"
#include "Resource.hpp"
#include "Texture.hpp"
#include "Utils.hpp"
#include "Logger.hpp"

namespace chaos{

class TerrainPrefab : public Resource
{
public:
    TerrainPrefab(Texture* heightmap, GLfloat minHeight, GLfloat maxHeight, GLfloat groundZeroHeightPercent);
    virtual ~TerrainPrefab();
    GLuint getTerrainId() const;
    GLuint getHeight(GLuint x, GLuint y) const;
    std::vector<GLfloat>* getVBOData();
    std::string getId();
protected:
    GLuint terrainId=0;
    static GLuint terrainCounter;
    std::vector<GLfloat> vboData;
    std::string strId;
};

}

#endif // TERRAINPREFAB_HPP
