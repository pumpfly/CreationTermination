cmake_minimum_required(VERSION 3.21)
project(gl3_creationTermination LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

set(PROGRAM "creationtermination")

add_executable(${PROGRAM}
    main.cpp
)

target_include_directories(${PROGRAM} PRIVATE src)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/
)
add_dependencies(${PROGRAM} copy_assets)

add_subdirectory(extern/brew_engine)

target_link_libraries(${PROGRAM} PRIVATE brew_engine)
