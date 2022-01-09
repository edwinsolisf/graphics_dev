#include "VertexArray.h"

#include <utility>

template<>
void VertexArrayLayout::addElement<GLfloat>(uint32_t count) noexcept
{
    elements_.emplace_back(GL_FLOAT, count, GL_FALSE);
    stride_ += VertexElement::sizeOfType(GL_FLOAT) * count;
}

template<>
void VertexArrayLayout::addElement<GLuint>(uint32_t count) noexcept
{
    elements_.emplace_back(GL_UNSIGNED_INT, count, GL_TRUE);
    stride_ += VertexElement::sizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexArrayLayout::addElement<GLubyte>(uint32_t count) noexcept
{
    elements_.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
    stride_ += VertexElement::sizeOfType(GL_UNSIGNED_BYTE) * count;
}

VertexArray::VertexArray(VertexArrayLayout layout)
    :layout_(std::move(layout))
{
    GLCALL(glGenVertexArrays(1, &id_));
    GLCALL(glBindVertexArray(id_));
}

VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1, &id_));
}

VertexElement::VertexElement(uint32_t type, uint32_t count, uint8_t normalize)
    :type_(type), count_(count), normalize_(normalize)
{
}

uint32_t VertexElement::sizeOfType(uint32_t type)
{
    switch(type)
    {
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        case GL_UNSIGNED_BYTE:
            return sizeof(GLbyte);
        case GL_BOOL:
            return sizeof(GLboolean);
        default:
            return 0;
    }
}
