#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "common.h"

struct ShaderInfo
{
    GLenum type;
    std::string filename;
    GLuint shader;
};

class Shader
{
public:
    GLuint mProgramId;
    Shader(ShaderInfo *);
    ~Shader();

    void use() const;

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value);
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value);
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value);
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value);
    void setVec2(const std::string &name, float x, float y);
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value);
    void setVec3(const std::string &name, float x, float y, float z);
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value);
    void setVec4(const std::string &name, float x, float y, float z, float w);
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat);
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat);
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat);

private:
    std::unordered_map<std::string, GLint> mUniformMap;

    std::string readFile(const std::string &filePath) const;
    void cacheUniformLocation(const std::string &name);
};

#endif // SHADER_H