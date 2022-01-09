#pragma once

#include <iostream>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, std::size_t size);
    ~VertexBuffer();

    uint32_t getId() const noexcept { return id_; }
private:
    uint32_t id_ = 0;
};
