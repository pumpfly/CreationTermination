cmake_minimum_required(VERSION 3.18)

project(CreationTermination)

# set variables for source files
set(SOURCE_FILES
        src/main.cpp
        src/CTGame.h
        src/Components/HealthComponent.h
        src/CTGame.cpp
        src/Systems/EnemySystem.cpp
        src/Systems/EnemySystem.h
        src/Systems/MissileSystem.h
        src/Components/MissileComponent.h
        src/Systems/MissileSystem.cpp
        src/Systems/PlayerSystem.h
        src/Systems/PlayerSystem.cpp
        src/Components/PlayerComponent.h
        src/Components/EnemyComponent.h
        src/Components/UiComponent.h
        src/Systems/IntroSystem.cpp
        src/Systems/IntroSystem.h
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