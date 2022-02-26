#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "BO.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "Vertex.h"

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

    auto green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    std::array<Vertex, 4> vertices = {
        Vertex{glm::vec3{-0.5f, +0.5f, 0.0f}, green},
        Vertex{glm::vec3{+0.5f, +0.5f, 0.0f}, green},
        Vertex{glm::vec3{+0.5f, -0.5f, 0.0f}, green},
        Vertex{glm::vec3{-0.5f, -0.5f, 0.0f}, green},
    };

    std::array<unsigned int, 6> indices = {0, 2, 3, 0, 1, 2};

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

    auto vao = VAO();
    auto vbo = BO(GL_ARRAY_BUFFER);
    auto ebo = BO(GL_ELEMENT_ARRAY_BUFFER);
    auto usage = GL_STATIC_DRAW;

    vao.set_attrib<Vertex>(vbo, 0, glm::vec3::length(), GL_FLOAT, GL_FALSE, (void*)offsetof(Vertex, position));
    vao.set_attrib<Vertex>(vbo, 1, glm::vec4::length(), GL_FLOAT, GL_FALSE, (void*)offsetof(Vertex, color));

    vbo.set_data(vertices, usage);
    ebo.set_data(indices, usage);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_program.use();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

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
