#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "Shader.h"
#include "ShaderProgram.h"

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>

std::string load_text(const std::string& path);

using namespace Minecraft;

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        std::cerr << "Couldn't initialize glfw\n";
        return -1;
    }

    window = glfwCreateWindow(1280, 720, "Minecraft", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    auto err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Error:" << glewGetErrorString(err) << "\n";
        glfwTerminate();
        return -1;
    }

    auto bg_color = glm::vec4(0.5f, 0.8f, 0.9f, 1.f);

    glClearColor(bg_color.r, bg_color.g, bg_color.b, bg_color.a);

    std::array<glm::vec3, 3> vertices = {
        glm::vec3{-0.5f, -0.5f, 0.0f},
        glm::vec3{0.0f, +0.5f, 0.0f},
        glm::vec3{+0.5f, -0.5f, 0.0f},
    };

    auto vs_source = load_text("../res/shaders/shader.vs");
    auto fs_source = load_text("../res/shaders/shader.fs");

    auto vs = Shader(vs_source, GL_VERTEX_SHADER);
    auto fs = Shader(fs_source, GL_FRAGMENT_SHADER);

    vs.compile();
    fs.compile();

    auto shader_program = ShaderProgram();
    shader_program.attach_shader(vs);
    shader_program.attach_shader(fs);
    shader_program.link();

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    auto usage = GL_STATIC_DRAW;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (void*)&vertices, usage);

    glVertexAttribPointer(0, vertices.size(), GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_program.use();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

std::string load_text(const std::string& path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
