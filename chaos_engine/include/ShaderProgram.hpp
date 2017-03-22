#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <vector>
#include <initializer_list>
#include <map>

#include "Export.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.hpp"

namespace chaos{

class CHAOS_EXPORT ShaderProgram
{
public:
    ShaderProgram(const std::initializer_list<std::pair<std::string, GLenum>> &v);
    ShaderProgram(const std::initializer_list<Shader> &v);
    virtual ~ShaderProgram();

    GLuint getId();
    void run();
    template<typename T>
    void setUniform(std::string uniId, T&& uniVal){
        if(mUniforms.find(uniId) == mUniforms.end()){
            mUniforms[uniId] = glGetUniformLocation(id, uniId.c_str());
        }
        setUniform(mUniforms[uniId], std::forward<T>(uniVal));
    }

    void setUniform(GLuint loc, const GLfloat &v);
    void setUniform(GLuint loc, const GLuint &v);
    void setUniform(GLuint loc, const glm::vec3 &v);
    void setUniform(GLuint loc, const glm::vec4 &v);
    void setUniform(GLint loc, const glm::mat4 &mx);
    GLint getAttribLocation(std::string& attribDescription);

private:
    GLuint id;
    std::map<std::string, GLuint> mUniforms;
};

}

#endif // SHADERPROGRAM_HPP
