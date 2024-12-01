cmake_minimum_required(VERSION 3.21)
project(brew_engine LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)

set(PROGRAM "brew_engine")

add_library(${PROGRAM}
        src/Window.cpp
        src/Color.cpp
        src/Mesh.cpp
        src/Shader.cpp
        lib/Shader.h
)

target_include_directories(${PROGRAM} PRIVATE src)
target_include_directories(${PROGRAM} PUBLIC lib extern/glfw-3.4/include extern/glm-1.0.1)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw-3.4)
add_subdirectory(extern/glm-1.0.1)

target_link_libraries(${PROGRAM} PRIVATE glad glfw glm)

