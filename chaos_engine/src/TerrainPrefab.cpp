#include "../include/TerrainPrefab.hpp"

GLuint chaos::TerrainPrefab::terrainCounter=0;

chaos::TerrainPrefab::TerrainPrefab(chaos::Texture* heightmap, GLfloat minHeight, GLfloat maxHeight, GLfloat groundZeroHeightPercent)
:Resource("terrain("+ heightmap->getFilePath() +")")
{
    strId="terrain("+ heightmap->getFilePath() +")";
    terrainId = terrainCounter++;
    SHOUT("terrain prefab!\n");
    SHOUT("%d x %d\n", heightmap->getWidth(), heightmap->getHeight());
    auto vectd = heightmap->getTextureData();
    std::vector<std::vector<GLfloat> >vecTmp;
    vecTmp.resize(vectd.size());
    for(GLuint i = 0; i < vectd.size(); i++){
        vecTmp[i].resize(vectd[i].size());
        for(GLuint j = 0; j < vectd[i].size(); j++){
            //SHOUT("(%.0f,%.0f,%.0f,%.0f)\n", vectd[i][j].r, vectd[i][j].g, vectd[i][j].b,vectd[i][j].a);
            GLfloat z = (vectd[i][j].r + vectd[i][j].g + vectd[i][j].b)/3.0;
            z = minHeight + (z/255.0)*(maxHeight-minHeight);
            vecTmp[i][j]=z;
        }
    }
    GLfloat groundLevel = (maxHeight-minHeight)*groundZeroHeightPercent;
    for(GLuint i = 0; i < vecTmp.size()-1; i++){
        for(GLuint j = 0; j < vecTmp[i].size()-1; j++){
            GLfloat x = i, z = j;
            vboData.insert(vboData.end(), {x,vecTmp[i][j]-groundLevel,z});
            vboData.insert(vboData.end(), {x,vecTmp[i][j+1]-groundLevel,z+1.0f});
            vboData.insert(vboData.end(), {x+1.0f,vecTmp[i+1][j]-groundLevel,z});

            vboData.insert(vboData.end(), {x,vecTmp[i][j+1]-groundLevel,z+1.0f});
            vboData.insert(vboData.end(), {x+1.0f,vecTmp[i+1][j]-groundLevel,z});
            vboData.insert(vboData.end(), {x+1.0f,vecTmp[i+1][j+1]-groundLevel,z+1.0f});
        }
    }
    /*vboData.insert(vboData.end(), {0,0,0});
    vboData.insert(vboData.end(), {1,0,0});
    vboData.insert(vboData.end(), {0,0,1});

    vboData.insert(vboData.end(), {1,0,0});
    vboData.insert(vboData.end(), {0,0,1});
    vboData.insert(vboData.end(), {1,0,1});*/
}

chaos::TerrainPrefab::~TerrainPrefab(){}

GLuint chaos::TerrainPrefab::getTerrainId() const {
    return terrainId;
}

GLuint chaos::TerrainPrefab::getHeight(GLuint x, GLuint y) const {
    return -1;
}

std::vector<GLfloat>* chaos::TerrainPrefab::getVBOData() {
    return &vboData;
}

std::string chaos::TerrainPrefab::getId(){
    return strId;
}
