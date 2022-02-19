cmake_minimum_required(VERSION 3.0.0)
project(Minecraft)

set(CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        include
)


target_link_libraries(${PROJECT_NAME} PRIVATE glfw GLEW::GLEW glm)
