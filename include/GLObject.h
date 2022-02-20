#pragma once
#include <GL/glew.h>

namespace Minecraft
{
class GLObject
{
  protected:
    GLuint handle;

  public:
    virtual void destroy() = 0;
    GLuint get_handle() const;
};
} // namespace Minecraft
