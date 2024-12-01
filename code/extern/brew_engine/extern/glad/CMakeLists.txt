cmake_minimum_required(VERSION 3.21)

project(GLAD C)
set(CMAKE_CXX_STANDARD 17)

# set glad header files variable
#set(HEADER_FILES include/glad/glad.h
#        include/KHR/khrplatform.h)

# set glad source files variable
set(SOURCE_FILES src/glad.c)

# add glad as a static library
add_library(glad STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(glad PUBLIC include)

# require C++ 17 compiler
#target_compile_features(glad PRIVATE cxx_std_17)

# specify the include directory for this static libray
#target_include_directories(glad PUBLIC include/)