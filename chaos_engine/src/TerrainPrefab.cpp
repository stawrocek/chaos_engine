#include "../include/TerrainPrefab.hpp"

GLuint chaos::TerrainPrefab::terrainCounter=0;
chaos::TerrainPrefab::TerrainPrefab(chaos::Texture* heightmap, GLfloat _minHeight, GLfloat _maxHeight)
:Resource("terrain("+ heightmap->getFilePath() +")"), minHeight(_minHeight), maxHeight(_maxHeight)
{
    strId="terrain("+ heightmap->getFilePath() +")";
    terrainId = terrainCounter++;
    SHOUT("terrain prefab!\n");
    terrainWidth = heightmap->getWidth();
    terrainDepth = heightmap->getHeight();
    SHOUT("%f x %f\n", terrainWidth, terrainDepth);
    auto vectd = heightmap->getTextureData();
    vecHeight.resize(vectd.size());
    for(GLuint i = 0; i < vectd.size(); i++){
        vecHeight[i].resize(vectd[i].size());
        for(GLuint j = 0; j < vectd[i].size(); j++){
            //SHOUT("(%.0f,%.0f,%.0f,%.0f)\n", vectd[i][j].r, vectd[i][j].g, vectd[i][j].b,vectd[i][j].a);
            GLfloat z = (vectd[i][j].r + vectd[i][j].g + vectd[i][j].b)/3.0;
            z = minHeight + (z/255.0)*(maxHeight-minHeight);
            vecHeight[i][j]=z;
        }
    }
    for(GLuint i = 0; i < vecHeight.size()-1; i++){
        for(GLuint j = 0; j < vecHeight[i].size()-1; j++){
            GLfloat x = i, z = j;
            addFloatToVBOAndNormalize(x,vecHeight[i][j],z);
            addFloatToVBOAndNormalize(x,vecHeight[i][j+1],z+1.0f);
            addFloatToVBOAndNormalize(x+1.0f,vecHeight[i+1][j],z);

            addFloatToVBOAndNormalize(x,vecHeight[i][j+1],z+1.0f);
            addFloatToVBOAndNormalize(x+1.0f,vecHeight[i+1][j],z);
            addFloatToVBOAndNormalize(x+1.0f,vecHeight[i+1][j+1],z+1.0f);
        }
    }
}

void chaos::TerrainPrefab::addFloatToVBOAndNormalize(GLfloat x, GLfloat y, GLfloat z){
    GLfloat xNorm = x/(terrainWidth-1);
    //GLfloat yNorm = (maxHeight-minHeight); //implement this!
    GLfloat yNorm = y;
    GLfloat zNorm = z/(terrainDepth-1.0);
    GLfloat u = xNorm;
    GLfloat v = zNorm;
    xNorm *= 2, xNorm -= 1.0f;  //[0,1] -> [-1,1]
    zNorm *= 2, zNorm -= 1.0f;  //[0,1] -> [-1,1]
    vboData.insert(vboData.end(), {xNorm, yNorm, zNorm});  //pos
    vboData.insert(vboData.end(), {u, v});  //uv
}

chaos::TerrainPrefab::~TerrainPrefab(){}

GLuint chaos::TerrainPrefab::getTerrainId() const {
    return terrainId;
}

GLfloat chaos::TerrainPrefab::getHeight(GLuint x, GLuint y) const {
    return vecHeight[y][x];
}

std::vector<GLfloat>* chaos::TerrainPrefab::getVBOData() {
    return &vboData;
}

std::string chaos::TerrainPrefab::getId(){
    return strId;
}
