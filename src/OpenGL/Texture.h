#pragma once

#include "OpenGLCore.h"

#include <string>

class Texture
{
public:
    explicit
    Texture(const std::string& fileName);
    ~Texture();

private:
    uint32_t id_ = 0;
};
