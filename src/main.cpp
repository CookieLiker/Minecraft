#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
#include <iostream>

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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
