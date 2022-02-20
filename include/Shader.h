#pragma once
#include <GL/glew.h>

#include "GLObject.h"

#include <string>

namespace Minecraft
{
class Shader : public GLObject
{
    GLenum type;

  public:
    Shader(const std::string& source, GLenum type);
    void destroy() override;
    void compile() const;
    GLenum get_type() const;
};
} // namespace Minecraft
