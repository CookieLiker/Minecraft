#pragma once
#include "BO.h"
#include "GLObject.h"

#include <array>

namespace Minecraft
{
class VAO : public GLObject
{
  public:
    VAO();
    void bind() const;
    void unbind() const;
    void destroy() override;

    template <class T>
    void set_attrib(const BO& vbo, GLuint index, int size, GLenum type, GLboolean normalized, void* offset)
    {
        bind();
        vbo.bind();
        glVertexAttribPointer(index, size, type, normalized, sizeof(T), (const void*)offset);
        glEnableVertexAttribArray(index);
    }
};
} // namespace Minecraft
