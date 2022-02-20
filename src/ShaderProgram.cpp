#include "ShaderProgram.h"

#include <iostream>

using namespace Minecraft;

ShaderProgram::ShaderProgram()
{
    handle = glCreateProgram();
}

void ShaderProgram::destroy()
{
    glDeleteProgram(handle);
}

void ShaderProgram::attach_shader(const Shader& shader)
{
    glAttachShader(handle, shader.get_handle());
}

void ShaderProgram::link() const
{
    int success = 0;

    glLinkProgram(handle);
    glGetProgramiv(handle, GL_LINK_STATUS, &success);

    if (success == GL_FALSE)
    {
        int length = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
        char* info_log = new char[length];
        glGetProgramInfoLog(handle, length, NULL, info_log);
        std::cerr << "error: " << info_log << "\n";
        delete[] info_log;
    }
}

void ShaderProgram::use() const
{
    glUseProgram(handle);
}
