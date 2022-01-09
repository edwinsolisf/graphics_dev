#pragma once

#include "OpenGLCore.h"

#include <cstddef>
#include <vector>

struct VertexElement
{
    uint32_t type_, count_;
    uint8_t normalize_;

    VertexElement(uint32_t type, uint32_t count, uint8_t normalize);
    std::size_t getOffset() const noexcept { return count_ * sizeOfType(type_); }

    static uint32_t sizeOfType(uint32_t type);
};

class VertexArrayLayout
{
public:
    template <typename T> void addElement(uint32_t count) noexcept;

    //template<> void addElement<GLfloat>(uint32_t count) noexcept;
    //template<> void addElement<GLuint >(uint32_t count) noexcept;
    //template<> void addElement<GLubyte>(uint32_t count) noexcept;

    const std::vector<VertexElement>& getElements() const noexcept { return elements_; }
    std::size_t getStride() const noexcept { return stride_; }

private:
    std::vector<VertexElement> elements_;
    std::size_t stride_ = 0;
};

class VertexArray
{
public:
    explicit VertexArray(VertexArrayLayout layout);
    ~VertexArray();

    const VertexArrayLayout& getLayout() const noexcept { return layout_; }
    uint32_t getId() const noexcept { return id_; }
private:
    uint32_t id_ = 0;
    VertexArrayLayout layout_;
};
