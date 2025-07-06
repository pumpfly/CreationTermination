cmake_minimum_required(VERSION 3.18)

project(LEIF C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# set leif source files variable
set(SOURCE_FILES
        leif.c
        vendor/glad/src/glad.c
)

# add glad as a static library
add_library(leif STATIC ${SOURCE_FILES})
add_subdirectory(vendor/cglm)
add_subdirectory(vendor/libclipboard)

target_include_directories(leif PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                        include/leif
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../glm/glm
                                        vendor/cglm/include
                                        vendor/libclipboard
                                        vendor/libclipboard/include
                                        ${CMAKE_CURRENT_BINARY_DIR}/vendor/libclipboard/include
                                        vendor/glad/include)

target_include_directories(leif PRIVATE
        vendor/stb_image
        vendor/stb_truetype
        vendor/stb_image_resize)

target_compile_definitions(leif PUBLIC LF_GLFW)
target_compile_options(leif PRIVATE -O3 -ffast-math)
target_link_libraries(leif PUBLIC OpenGL::GL glfw cglm clipboard)

find_package(OpenGL REQUIRED )