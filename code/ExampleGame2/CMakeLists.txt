cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES
        src/main.cpp
        src/ExampleGame.h
        src/GameOverScreen.h
        src/Health.h
        src/Position.h
        src/RenderSystem.h)

set(EXE_FILE ExampleGame2)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE BrewEngine)