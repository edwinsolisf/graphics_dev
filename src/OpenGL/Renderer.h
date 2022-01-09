#pragma once

#include "OpenGLCore.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

namespace Renderer
{

    template <typename T> void bindObject(const T& obj);

    //template <> void bindObject(const VertexBuffer& obj);
    //template <> void bindObject(const IndexBuffer& obj);
    //template <> void bindObject(const VertexArray& obj);
    //template <> void bindObject(const Shader& obj);

    void drawElements(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexArray& vao, const Shader& shader);

} //namespace Renderer
