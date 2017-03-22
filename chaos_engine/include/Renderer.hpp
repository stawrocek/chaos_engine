#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Export.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <unordered_map>
#include <vector>

namespace chaos{

class Camera;
class ShaderProgram;
class VertexArray;
class MeshPrefab;
class Window;

class CHAOS_EXPORT Renderer{
public:
    Renderer(Window* w);
    virtual ~Renderer();

    //Shaders
    ShaderProgram* addShader(const std::initializer_list<std::pair<std::string, GLenum>> &iniListShader, std::string id);
    ShaderProgram* getShader(std::string id);
    void removeShader(std::string id);

    //VAO

    VertexArray* addVAO(GLuint vertsSize, GLuint colorSize, GLuint uvSize, GLuint dataSize, std::vector<GLfloat>* vec, std::string id);
    VertexArray* getVAO(std::string id);
    void removeVAO(std::string id);
    void initEngineStuff();
    void addMeshVAO(MeshPrefab* mesh);

    glm::mat4 getCamCombined();
    void setCamCombined(glm::mat4 mx);
    void setTargetWindow(Window* _win);
    Window* getTargetWindow();
    //slow af
    void drawDebugLine(glm::vec3 start, glm::vec3 end, glm::vec4 color);
    Camera* getActiveCamera();
    void setActiveCamera(Camera* cam);

private:
    std::unordered_map<std::string , ShaderProgram*> cacheShaders;
    std::unordered_map<std::string , VertexArray*> cacheVAO;
    glm::mat4 camCombined = glm::mat4();
    Window* win = nullptr;
    Camera* activeCamera = nullptr;
};

}

#endif //RENDERER_HPP


