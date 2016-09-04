#include "MeshPrefab.hpp"

using namespace chaos;

GLuint MeshPrefab::meshCounter = 0;

MeshPrefab::MeshPrefab(std::string fpath)
    :Resource(fpath)
{
    load(fpath);
    meshId = meshCounter++;
}

GLboolean MeshPrefab::load(std::string fpath){
    loadObj(fpath);
}

GLboolean MeshPrefab::loadObj(std::string fpath){
    FILE * file = fopen(fpath.c_str(), "rb");
    if( file == nullptr )
    {
        return false;
    }
    vecVertices.clear();
    vecVerticesIndices.clear();
    vecUV.clear();
    vecUVIndices.clear();
    vecNormals.clear();
    vecNormalsIndices.clear();

    while(true)
    {
        char header[128];
        int retCode = fscanf(file, "%s", header);
        if(retCode == EOF)
        {
            break;
        }
        if (strcmp(header, "v") == 0)
        {
            glm::vec3 vert;
            fscanf(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
            vecVertices.push_back(vert);
        }
        else if (strcmp(header, "vt") == 0)
        {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            vecUV.push_back(uv);
        }
        else if (strcmp(header, "vn") == 0)
        {
            glm::vec3 vecNorm;
            fscanf(file, "%f %f %f\n", &vecNorm.x, &vecNorm.y, &vecNorm.z );
            vecNormals.push_back(vecNorm);
        }
        else if(strcmp(header, "f") == 0)
        {
            GLuint vertIdx[3], uvIdx[3], normalIdx[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                 &vertIdx[0], &uvIdx[0], &normalIdx[0],
                                 &vertIdx[1], &uvIdx[1], &normalIdx[1],
                                 &vertIdx[2], &uvIdx[2], &normalIdx[2]);
            if (matches != 9)
            {
                printf(".obj 'f' section should have contain 9 floats, instead %d given\n", matches);
                return false;
            }
            vecVerticesIndices.push_back(vertIdx[0]-1);
            vecVerticesIndices.push_back(vertIdx[1]-1);
            vecVerticesIndices.push_back(vertIdx[2]-1);
            vecUVIndices.push_back(uvIdx[0]-1);
            vecUVIndices.push_back(uvIdx[1]-1);
            vecUVIndices.push_back(uvIdx[2]-1);
            vecNormalsIndices.push_back(normalIdx[0]-1);
            vecNormalsIndices.push_back(normalIdx[1]-1);
            vecNormalsIndices.push_back(normalIdx[2]-1);
        }
    }
    recalculateVertexData();
    return true;
}

void MeshPrefab::recalculateVertexData(){
    /*vboData = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };*/
    vboData.clear();
    for(unsigned int i=0; i<vecVerticesIndices.size(); i++)
    {
        glm::vec3 vertex = vecVertices[vecVerticesIndices[i]];
        glm::vec2 uv = vecUV[vecUVIndices[i]];
        glm::vec3 normal = vecNormals[vecNormalsIndices[i]];

        vboData.push_back(vertex.x);   //x
        vboData.push_back(vertex.y);   //y
        vboData.push_back(vertex.z);   //z
        vboData.push_back(normal.x);
        vboData.push_back(normal.y);
        vboData.push_back(normal.z);
        vboData.push_back(uv.x);       //u
        vboData.push_back(uv.y);       //v
    }
}

std::vector<GLfloat>* MeshPrefab::getVBOData(){
    return &vboData;
}

GLuint MeshPrefab::getMeshId(){
    return meshId;
}
