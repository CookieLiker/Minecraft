#include "Shader.h"

#include <iostream>

using namespace Minecraft;

Shader::Shader(const std::string& source, GLenum type) : type{type}
{
    handle = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(handle, 1, &src, 0);
}

void Shader::destroy()
{
    glDeleteShader(handle);
}

void Shader::compile() const
{
    int success = 0;

    glCompileShader(handle);
    glGetShaderiv(handle, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        int length = 0;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);
        char* info_log = new char[length];
        glGetShaderInfoLog(handle, length, NULL, info_log);
        std::cerr << "error: " << info_log << "\n";
        delete[] info_log;
    }
}

GLenum Shader::get_type() const
{
    return type;
}
