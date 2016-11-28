#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "Export.hpp"

#include <vector>
#include <initializer_list>
#include <algorithm>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

namespace chaos{

class CHAOS_EXPORT ShaderProgram
{
public:
    ShaderProgram(const std::initializer_list<std::pair<std::string, GLenum>> &v);
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

    void setUniform(GLuint loc, const GLfloat &v){
        glUniform1f(loc, v);
    }

    void setUniform(GLuint loc, const GLuint &v){
        glUniform1i(loc, v);
    }

    void setUniform(GLuint loc, const glm::vec4 &v){
        glUniform4f(loc, v.x, v.y, v.z, v.w);
    }

    void setUniform(GLint loc, const glm::mat4 &mx) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mx));
    }

private:
    GLuint id;
    std::map<std::string, GLuint> mUniforms;
};

}

#endif // SHADERPROGRAM_HPP
