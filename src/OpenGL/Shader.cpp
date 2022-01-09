#include "Shader.h"

#include <fstream>
#include <iostream>

ShaderSource::ShaderSource(const std::string& fileName)
{
    std::ifstream file = std::ifstream(fileName);
    ShaderType type = ShaderType::NONE;

    if (file.fail())
    {
        std::cerr << "Could not open file " << fileName << std::endl;
    }

    std::string buffer;
    std::string source;
    while(std::getline(file, buffer))
    {
        if (buffer.find("#SHADER VERTEX") != std::string::npos)
        {
            type = ShaderType::VERTEX;
            name_ = buffer.substr(strlen("#SHADER VERTEX"));
        }
        else if (buffer.find("#SHADER FRAGMENT") != std::string::npos)
        {
            type = ShaderType::FRAGMENT;
            name_ = buffer.substr(strlen("#SHADER FRAGMENT"));
        }
        else if (buffer.find("#SHADER GEOMETRY") != std::string::npos)
        {
            type = ShaderType::GEOMETRY;
            name_ = buffer.substr(strlen("#SHADER GEOMETRY"));
        }
        else
        {
            source += buffer;
            source += '\n';
        }
    }

    if (type == ShaderType::NONE)
        return;

    GLCALL(id_ = glCreateShader(static_cast<GLuint>(type)));
    const char* sourceStr = source.c_str();
    GLCALL(glShaderSource(id_, 1, &sourceStr, nullptr));
    compile();
}

ShaderSource::~ShaderSource()
{
    GLCALL(glDeleteShader(id_));
}

void ShaderSource::compile() const
{
    if (!compiled_)
    {
        GLCALL(glCompileShader(id_));
        GLint compiled = 0;
        GLCALL(glGetShaderiv(id_, GL_COMPILE_STATUS, &compiled));
        compiled_ = static_cast<bool>(compiled);

        if (!compiled_)
        {
            char buff[512];
            GLCALL(glGetShaderInfoLog(id_, sizeof(buff), nullptr, buff));
            std::cerr << "[OPENGL ERROR]: Shader compilation - " << buff << std::endl;
        }
    }
}

Shader::Shader()
{
    GLCALL(id_ = glCreateProgram());
}

Shader::~Shader()
{
    GLCALL(glDeleteProgram(id_));
}

bool Shader::attachSource(std::unique_ptr<ShaderSource> source)
{
    source->compile();

    if (source->isCompiled())
    {
        GLCALL(glAttachShader(id_, source->getId()));
        sources_.push_back(std::move(source));
        return true;
    }

    return false;
}

void Shader::linkProgram() const
{
    if (!linked_)
    {
        GLCALL(glLinkProgram(id_));
        GLint linked = 0;
        GLCALL(glGetProgramiv(id_, GL_LINK_STATUS, &linked));
        linked_ = static_cast<bool>(linked);

        if (!linked_)
        {
            char buff[512];
            GLCALL(glGetProgramInfoLog(id_, sizeof(buff), nullptr, buff));
            std::cerr << "[OPENGL ERROR]: Shader linking - " << buff << std::endl;
        }
    }
}

int32_t Shader::getUniformLocation(const char* uniform) const
{
    auto iter = uniformLocationCache_.find(uniform);
    if (iter != uniformLocationCache_.cend())
        return iter->second;

    GLCALL(int32_t location = glGetUniformLocation(id_, uniform));

    if (location != -1)
        return uniformLocationCache_[uniform] = location;

    std::cerr << "[OPENGL WARN]: Uniform \"" << uniform << "\" not found" << std::endl;
    return -1;
}

void Shader::setUniformVec3f(const char* uniform, const stm::vec3f& vec) const
{
    GLCALL(glUniform3fv(getUniformLocation(uniform), 1, vec.GetData()));
}

void Shader::setUniformVec4f(const char* uniform, const stm::vec4f& vec) const
{
    GLCALL(glUniform4fv(getUniformLocation(uniform), 1, vec.GetData()));
}

void Shader::setUniformMat4f(const char* uniform, const stm::mat4f& mat) const
{
    GLCALL(glUniformMatrix4fv(getUniformLocation(uniform), 1, GL_TRUE, mat.GetData()));
}
