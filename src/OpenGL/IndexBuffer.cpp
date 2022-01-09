#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t indexCount)
    :indexCount_(indexCount)
{
    GLCALL(glGenBuffers(1, &id_));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &id_));
}
