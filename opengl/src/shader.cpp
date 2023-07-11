#include "shader.h"

Shader::Shader(ShaderInfo *sl)
{
    if (sl == NULL)
        return;

    mProgramId = glCreateProgram();

    bool failedFlag = false;
    // load source
    ShaderInfo *entry = sl;
    while (entry->type != GL_NONE)
    {
        // read shader
        std::string shaderSource = readFile(entry->filename);
        DEBUG_PRINTF("Read Shader from path: %s \n", entry->filename.c_str());
        // compile shader
        GLuint shaderId    = glCreateShader(entry->type);
        const char *source = shaderSource.c_str();
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);
        GLint compilationStatus;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);
        if (compilationStatus != GL_TRUE)
        {
            ERR_PRINT("Shader Complie failed!");

            GLint logLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

            char *log = new char[logLength];
            glGetShaderInfoLog(shaderId, logLength, nullptr, log);

            ERR_PRINT(log);
            delete[] log;

            failedFlag = true;
            break;
        }
        else
        {
            entry->shader = shaderId;
        }
        // attach shader
        glAttachShader(mProgramId, shaderId);
        ++entry;
    }

    // link program
    glLinkProgram(mProgramId);
    GLint linked;
    glGetProgramiv(mProgramId, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        GLsizei len;
        glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &len);

        GLchar *log = new GLchar[len + 1];
        glGetProgramInfoLog(mProgramId, len, &len, log);
        ERR_PRINT("Shader linking failed: ");
        ERR_PRINT(log);
        delete[] log;

        failedFlag = true;
    }

    // release when failed
    if (failedFlag)
    {
        for (entry = sl; entry->type != GL_NONE; ++entry)
        {
            glDeleteShader(entry->shader);
        }
        glDeleteProgram(mProgramId);
        mProgramId = -1;
    }
}

Shader::~Shader()
{
    glDeleteProgram(mProgramId);
}

void Shader::use() const
{
    glUseProgram(mProgramId);
}

void Shader::setBool(const std::string &name, bool value)
{
    cacheUniformLocation(name);
    glUniform1i(mUniformMap.at(name), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
    cacheUniformLocation(name);
    glUniform1i(mUniformMap.at(name), value);
}

void Shader::setFloat(const std::string &name, float value)
{
    cacheUniformLocation(name);
    glUniform1f(mUniformMap.at(name), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value)
{
    cacheUniformLocation(name);
    glUniform2fv(mUniformMap.at(name), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y)
{
    cacheUniformLocation(name);
    glUniform2f(mUniformMap.at(name), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value)
{
    cacheUniformLocation(name);
    glUniform3fv(mUniformMap.at(name), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
    cacheUniformLocation(name);
    glUniform3f(mUniformMap.at(name), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value)
{
    cacheUniformLocation(name);
    glUniform4fv(mUniformMap.at(name), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
    cacheUniformLocation(name);
    glUniform4f(mUniformMap.at(name), x, y, z, w);
}
void Shader::setMat2(const std::string &name, const glm::mat2 &mat)
{
    cacheUniformLocation(name);
    glUniformMatrix2fv(mUniformMap.at(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat)
{
    cacheUniformLocation(name);
    glUniformMatrix3fv(mUniformMap.at(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
    cacheUniformLocation(name);
    glUniformMatrix4fv(mUniformMap.at(name), 1, GL_FALSE, &mat[0][0]);
}

std::string Shader::readFile(const std::string &filePath) const
{
    std::ifstream file(filePath);
    std::stringstream content;
    content << file.rdbuf();
    file.close();
    return content.str();
}

void Shader::cacheUniformLocation(const std::string &name)
{
    if (mUniformMap.find(name) == mUniformMap.end())
    {
        GLint location    = glGetUniformLocation(mProgramId, name.c_str());
        mUniformMap[name] = location;
    }
}