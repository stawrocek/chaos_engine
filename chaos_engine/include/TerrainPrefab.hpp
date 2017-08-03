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
    TerrainPrefab(Texture* heightmap, GLfloat _minHeight, GLfloat _maxHeight, GLfloat _groundZeroHeightPercent);
    virtual ~TerrainPrefab();
    GLuint getTerrainId() const;
    GLfloat getHeight(GLuint x, GLuint y) const;
    std::vector<GLfloat>* getVBOData();
    std::string getId();
protected:
    GLfloat terrainWidth, terrainDepth;
    GLfloat minHeight, maxHeight;
    GLfloat groundZeroPercent;
    void addFloatToVBOAndNormalize(GLfloat x, GLfloat y, GLfloat z);
    GLuint terrainId=0;
    static GLuint terrainCounter;
    std::vector<GLfloat> vboData;
    std::vector<std::vector<GLfloat> > vecHeight;
    std::string strId;
};

}

#endif // TERRAINPREFAB_HPP
