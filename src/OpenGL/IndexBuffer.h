#pragma once

#include "OpenGLCore.h"

class IndexBuffer
{
public:
    IndexBuffer(const uint32_t* data, uint32_t indexCount);
    ~IndexBuffer();

    uint32_t getId() const noexcept { return id_; }
    uint32_t getIndexCount() const noexcept { return indexCount_; }

private:
    uint32_t id_ = 0;
    uint32_t indexCount_ = 0;
};
