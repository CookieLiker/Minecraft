#pragma once
#include <GL/glew.h>

#include "GLObject.h"
#include "Shader.h"

namespace Minecraft
{
class ShaderProgram : public GLObject
{
  public:
    ShaderProgram();
    void destroy() override;
    void attach_shader(const Shader& shader);
    void link() const;
    void use() const;
};
} // namespace Minecraft
