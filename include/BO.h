#pragma once
#include "GLObject.h"

#include <array>

namespace Minecraft
{
class BO : public GLObject
{
  private:
    size_t size;
    GLenum type;

  public:
    BO(GLenum type);
    void bind() const;
    void unbind() const;
    void destroy() override;

    GLenum get_type() const;

    template <class T, size_t N> void set_data(const std::array<T, N>& data, int usage)
    {
        glBindBuffer(type, handle);
        glBufferData(type, sizeof(data), (void*)&data, usage);
        size = data.size();
    }
};
} // namespace Minecraft
