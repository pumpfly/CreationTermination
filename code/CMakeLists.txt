cmake_minimum_required(VERSION 3.18)
project(gl3)

set(CMAKE_CXX_STANDARD 17)

add_link_options(-static-libstdc++ -static-libgcc -static -lpthread -lwinpthread)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/leif)
add_subdirectory(extern/glm)
add_subdirectory(extern/soloud)
add_subdirectory(BrewEngine)

add_subdirectory(CreationTermination)



