cmake_minimum_required(VERSION 3.21)
project(gl3_wp5)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/soloud)
add_subdirectory(BrewEngine)

add_subdirectory(game)
add_subdirectory(ExampleGame1)
add_subdirectory(ExampleGame2)



