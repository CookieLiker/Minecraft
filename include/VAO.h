#pragma once
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

    template <class T, size_t N>
    void set_attrib(GLuint index, const std::array<T, N>& vertices, GLenum type, GLboolean normalized, void* offset)
    {
        glBindVertexArray(handle);
        glVertexAttribPointer(index, vertices.size(), type, normalized, sizeof(T), (const void*)offset);
        glEnableVertexAttribArray(index);
    }
};
} // namespace Minecraft
