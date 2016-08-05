cmake_minimum_required( VERSION 3.0.0 )

project( compilers-lark NONE )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_PREFIX_PATH}/share/cmake/Modules" )

include( BBProject )

bbproject_initialize()
bbproject_setup()

add_subdirectory( "src/groups" )

bbproject_print_summary()
