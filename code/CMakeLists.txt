cmake_minimum_required(VERSION 3.29)
project(GameLab3)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(BrewEngine)

add_subdirectory(extern/glad)

add_subdirectory(extern/glfw)

add_subdirectory(extern/glm)

add_subdirectory(extern/soloud)

add_subdirectory(game)



