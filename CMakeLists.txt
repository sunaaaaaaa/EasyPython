cmake_minimum_required(VERSION 2.8)

project(easyPy)
#cmake显示编译命令
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall")

include_directories(./src/object/)
include_directories(./src/util/)
include_directories(./src/code/)
include_directories(./src/)

add_executable(test 
         src/main.cc
         src/object/object.cc
         src/object/String.cc
         src/object/integer.cc
         src/code/code_object.cc
         src/code/binary_parser.cc
         src/runtime/interpreter.cc
         src/runtime/universe.cc
         src/util/map.cc)

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
