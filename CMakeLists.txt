# CMakeLists.txt
cmake_minimum_required(VERSION 3.0.0)

include(cmake/larkutil.cmake)

project(Lark)

add_compile_options("-std=c++14")

add_subdirectory("src/groups")
