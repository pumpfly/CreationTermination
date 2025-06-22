cmake_minimum_required(VERSION 3.18)

project(CreationTermination)

# set variables for source files
set(SOURCE_FILES
        src/main.cpp
        src/CTGame.h
        src/Components/HealthComponent.h
        src/Player.h
        src/CTGame.cpp
        src/Systems/RenderingSystem.cpp
        src/Systems/RenderingSystem.h
        src/Systems/InputSystem.cpp
        src/Systems/InputSystem.h
)

# set executable name
set(EXE_FILE CreationTermination)

# add the executable target
add_executable(${EXE_FILE} ${SOURCE_FILES})

# require C++ 17 compiler
target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

# link with dependencies
target_link_libraries(${EXE_FILE} PRIVATE BrewEngine)

target_compile_definitions(${EXE_FILE} PRIVATE ASSET_ROOT=./assets/)

add_custom_target(copy_dir_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/CreationTermination/assets)
add_dependencies(${EXE_FILE} copy_dir_assets)