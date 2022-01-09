#pragma once

#include "OpenGLCore.h"

#include "stm/matrix.h"
#include "stm/vector.h"

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

enum class ShaderType : GLuint
{
    VERTEX = GL_VERTEX_SHADER, FRAGMENT = GL_FRAGMENT_SHADER, GEOMETRY = GL_GEOMETRY_SHADER, NONE
};

class ShaderSource
{
public:

    explicit
    ShaderSource(const std::string& fileName);
    ~ShaderSource();

    void compile() const;

    bool isCompiled() const noexcept { return compiled_; }
    uint32_t getId() const noexcept { return id_; }

private:
    std::string name_;
    uint32_t id_ = 0;
    mutable bool compiled_ = false;
};

class Shader
{
public:
    Shader();
    ~Shader();

    bool attachSource(std::unique_ptr<ShaderSource> source);
    void linkProgram() const;

    bool isLinked() const noexcept { return linked_; }
    uint32_t getId() const noexcept { return id_; }

    void setUniformVec3f(const char* uniform, const stm::vec3f& vec) const;
    void setUniformVec4f(const char* uniform, const stm::vec4f& vec) const;
    void setUniformMat4f(const char* uniform, const stm::mat4f& mat) const;

    int32_t getUniformLocation(const char* uniform) const;

private:
    std::vector<std::unique_ptr<ShaderSource>> sources_;
    mutable std::unordered_map<const char*, uint32_t> uniformLocationCache_;
    int32_t id_ = 0;
    mutable bool linked_ = false;
};
