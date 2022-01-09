#include "VertexBuffer.h"

#include "OpenGLCore.h"

VertexBuffer::VertexBuffer(const void* data, std::size_t size)
{
    GLCALL(glGenBuffers(1, &id_));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, id_));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &id_));
}
