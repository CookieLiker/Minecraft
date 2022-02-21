#include "BO.h"

using namespace Minecraft;

BO::BO(GLenum type) : type{type}
{
    glGenBuffers(1, &handle);
}

void BO::bind() const
{
    glBindBuffer(type, handle);
}

void BO::unbind() const
{
    glBindBuffer(type, 0);
}

void BO::destroy()
{
    glDeleteBuffers(1, &handle);
}

GLenum BO::get_type() const
{
    return type;
}
