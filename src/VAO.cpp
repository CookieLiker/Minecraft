#include "VAO.h"

using namespace Minecraft;

VAO::VAO()
{
    glGenVertexArrays(1, &handle);
}

void VAO::bind() const
{
    glBindVertexArray(handle);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}

void VAO::destroy()
{
    glDeleteVertexArrays(1, &handle);
}
