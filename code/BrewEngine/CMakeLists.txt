cmake_minimum_required(VERSION 3.18)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/**.h")
file(GLOB_RECURSE PRIVATE_HEADER_LIST CONFIGURE_DEPENDS "src/**.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "src/**.cpp")

set(ENGINE_NAME BrewEngine)

add_library(${ENGINE_NAME} ${HEADER_LIST} ${PRIVATE_HEADER_LIST} ${SOURCE_LIST}
        include/brewEngine/ecs/System.h
        include/brewEngine/ecs/ecs.h
        include/brewEngine/ecs/Component.h
        include/brewEngine/ecs/ComponentManager.h
        src/ecs/ComponentManager.cpp
        include/brewEngine/ecs/Entity.h
        include/brewEngine/ecs/EntityManager.h
        src/ecs/EntityManager.cpp
        include/brewEngine/Context.h
        src/Context.cpp
        include/brewEngine/sceneGraph/Transform.h
        src/sceneGraph/Transform.cpp
        include/brewEngine/sceneGraph/SceneGraphPruner.h
        include/brewEngine/sceneGraph/SceneGraphUpdater.h
        include/brewEngine/input/Bitmanipulation.h
        src/rendering/GeometryRenderer.cpp
        include/brewEngine/Config.h
        include/brewEngine/Assets.h
        include/brewEngine/stb_image.h
)

target_compile_features(${ENGINE_NAME} PRIVATE cxx_std_17)
set_target_properties(${ENGINE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw glm soloud)

if(WIN32)
    target_link_libraries(${ENGINE_NAME} PUBLIC winmm)
endif()

target_include_directories(${ENGINE_NAME} PUBLIC include/)
