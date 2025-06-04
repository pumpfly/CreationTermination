cmake_minimum_required(VERSION 3.18)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/**.h")
file(GLOB_RECURSE PRIVATE_HEADER_LIST CONFIGURE_DEPENDS "src/**.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "src/**.cpp")

set(HEADER_LIST include/brewEngine/HelloWorld.h)
set(SOURCE_LIST src/HelloWorld.cpp
        include/brewEngine/Game.h
        src/Game.cpp)
set(ENGINE_NAME BrewEngine)

add_library(${ENGINE_NAME} ${HEADER_LIST} ${SOURCE_LIST})

target_compile_features(${ENGINE_NAME} PRIVATE cxx_std_17)
set_target_properties(${ENGINE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw glm soloud)

target_include_directories(${ENGINE_NAME} PUBLIC include/)
