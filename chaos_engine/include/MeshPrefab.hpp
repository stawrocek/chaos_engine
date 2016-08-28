#ifndef MESH_PREFAB_HPP
#define MESH_PREFAB_HPP

#include "VertexArray.hpp"
#include "Resource.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <string>
#include <fstream>
#include <cstring>

namespace chaos
{
class MeshPrefab: public Resource
{
public:
    MeshPrefab(std::string fpath);
    GLboolean load(std::string fpath);
    GLboolean loadObj(std::string fpath);
    void recalculateVertexData();
    std::vector<GLfloat>* getVBOData();
    GLuint getMeshId();


protected:
    std::vector<glm::vec3> vecVertices;
    std::vector<glm::vec2> vecUV;
    std::vector<glm::vec3> vecNormals;

    std::vector<GLuint> vecVerticesIndices;
    std::vector<GLuint> vecUVIndices;
    std::vector<GLuint> vecNormalsIndices;

    std::vector<GLfloat> vboData;

    static GLuint meshCounter;
    GLuint meshId=0;
};

}

#endif //MESH_PREFAB_HPP


