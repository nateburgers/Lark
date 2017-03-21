# larkutil.cmake                                                     -*-CMake-*-

#@PURPOSE: Provide a suite of utility functions for compiling with BDE metadata.
#
#@DESCRIPTION:
#

set(CMAKE_BINARY_DIR       "${PROJECT_SOURCE_DIR}/build")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH    "${CMAKE_BINARY_DIR}/lib")

set(LARK_INCLUDE_PATH)

function(lark_add_package name)
    file(STRINGS "${name}/package/${name}.mem" members)
    add_library("${name}" STATIC)
    list(APPEND "${LARK_INCLUDE_PATH}" "${name}")
    target_include_directories("${name}" SYSTEM PUBLIC "${LARK_INCLUDE_PATH}")
    foreach(member ${members})
        target_sources("${name}" PRIVATE "${name}/${member}.cpp")
    endforeach()

    file(STRINGS "${name}/package/${name}.dep" dependencies)
    foreach(dependency ${dependencies})
        target_link_libraries("${name}" "${dependency}")
    endforeach()
endfunction()