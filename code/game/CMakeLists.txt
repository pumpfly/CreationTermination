cmake_minimum_required(VERSION 3.18)

# set variables for source files
set(SOURCE_FILES src/main.cpp
        src/Game.cpp
        src/Game.h
        src/rendering/Shader.cpp
        src/rendering/Shader.h
        src/entities/Entity.cpp
        src/entities/Entity.h
        src/entities/Witch.cpp
        src/entities/Witch.h
        src/Assets.h
        src/entities/Creature.cpp
        src/entities/Creature.h
        src/entities/Missiles.cpp
        src/entities/Missiles.h
        src/Input/Input.cpp
        src/Input/Input.h
        src/input/Bitmanipulation.h
        src/entities/Shield.cpp
        src/entities/Shield.h
        src/entities/bats.cpp
        src/entities/bats.h
        src/rendering/SpriteRenderer.cpp
        src/rendering/SpriteRenderer.h
        src/rendering/Texture2D.cpp
        src/rendering/Texture2D.h
        src/stb_image.h
        src/rendering/ResourceManager.cpp
        src/rendering/ResourceManager.h
        src/SpatialGridManager.h
        src/SpatialGridManager.cpp
        src/rendering/GeometryRenderer.h
        src/rendering/GeometryRenderer.cpp
        src/BackgroundManager.cpp
        src/BackgroundManager.h
)

# set executable name
set(EXE_FILE Game)

# add the executable target
add_executable(${EXE_FILE} ${SOURCE_FILES})

# require C++ 17 compiler
target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

# link with dependencies
target_link_libraries(${EXE_FILE} PRIVATE glad glfw glm soloud)

target_compile_definitions(${EXE_FILE} PRIVATE ASSET_ROOT=./assets/)

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/game/assets)
add_dependencies(${EXE_FILE} copy_assets)