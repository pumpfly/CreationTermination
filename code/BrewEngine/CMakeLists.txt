cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/HelloWorld.h src/HelloWorld.cpp)
set(ENGINE_NAME BrewEngine)

add_library(${ENGINE_NAME} ${SOURCE_FILES})

target_compile_features(${ENGINE_NAME} PRIVATE cxx_std_17)
set_target_properties(${ENGINE_NAME} PROPERTIES LINKER_LANGUAGE CXX)