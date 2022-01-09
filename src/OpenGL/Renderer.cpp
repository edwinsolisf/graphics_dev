#include "Renderer.h"

namespace Renderer
{
    template <>
    void bindObject(const VertexBuffer& obj)
    {
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, obj.getId()));
    }

    template <>
    void bindObject(const IndexBuffer& obj)
    {
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.getId()));
    }

    template <>
    void bindObject(const VertexArray& obj)
    {
        GLCALL(glBindVertexArray(obj.getId()));

        //Enable attributes
        std::size_t offset = 0;
        std::size_t stride = obj.getLayout().getStride();
        const auto& elements = obj.getLayout().getElements();

        for (std::size_t i = 0; i < elements.size(); ++i)
        {
            const auto& element = elements[i];
            GLCALL(glVertexAttribPointer(i, element.count_, element.type_, element.normalize_, stride, (const void*)offset));
            GLCALL(glEnableVertexAttribArray(i));
            offset += element.getOffset();
        }

    }

    template <>
    void bindObject(const Shader& obj)
    {
        GLCALL(glUseProgram(obj.getId()));
    }

    void drawElements(const VertexBuffer& vbo, const IndexBuffer& ibo, const VertexArray& vao, const Shader& shader)
    {
        bindObject(vao);
        bindObject(vbo);
        bindObject(ibo);
        bindObject(shader);

        GLCALL(glDrawElements(GL_TRIANGLES, ibo.getIndexCount(), GL_UNSIGNED_INT, (const void*)0));
    }
} //namespace Renderer
