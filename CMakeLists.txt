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
         src/code/binary_parser.cc
         src/code/code_object.cc
         src/runtime/interpreter.cc
         src/object/object.cc
         src/object/Klass.cc
         src/object/List.cc
         src/object/dict.cc
         src/object/iter.cc
         src/object/String.cc
         src/object/integer.cc
         src/object/method.cc
         src/object/function.cc
         src/object/string_table.cc
         src/runtime/universe.cc
         src/runtime/frame.cc
         src/runtime/cell.cc
         src/runtime/space.cc
         src/memory/oopClosure.cc
         src/util/map.cc
         src/util/stack.cc
         src/util/array_list.cc)

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
