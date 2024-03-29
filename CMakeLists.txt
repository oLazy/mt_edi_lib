cmake_minimum_required(VERSION 3.10)
project(mt_edi_lib)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")
#											#
#											#
#											#
#                    Boost config			#
#											#
#											#
find_package(Boost REQUIRED serialization iostreams system filesystem timer program_options)


if (Boost_FOUND)
    message("BOOST FOUND")
    message("VERSION: ${Boost_VERSION}")
endif()

#find_package(ROOT COMPONENTS RooStats)
add_library(Boost_iostreams STATIC IMPORTED)
add_library(Boost_serialization STATIC IMPORTED)
add_library(Boost_system STATIC IMPORTED)
add_library(Boost_filesystem STATIC IMPORTED)
add_library(Boost_timer STATIC IMPORTED)
add_library(Boost_chrono STATIC IMPORTED)
add_library(Boost_program_options STATIC IMPORTED)

set_target_properties(Boost_serialization PROPERTIES
        IMPORTED_LOCATION "${Boost_LIBRARY_DIRS}/libboost_serialization.a")
set_target_properties(Boost_iostreams PROPERTIES
        IMPORTED_LOCATION "${Boost_LIBRARY_DIRS}/libboost_iostreams.a")
set_target_properties(Boost_system PROPERTIES
        IMPORTED_LOCATION "${Boost_LIBRARY_DIRS}/libboost_system.a")
set_target_properties(Boost_filesystem PROPERTIES
        IMPORTED_LOCATION "${Boost_LIBRARY_DIRS}/libboost_filesystem.a")
set_target_properties(Boost_timer PROPERTIES
        IMPORTED_LOCATION "${Boost_LIBRARY_DIRS}/libboost_timer.a")
set_target_properties(Boost_chrono PROPERTIES
        IMPORTED_LOCATION "${Boost_LIBRARY_DIRS}/libboost_chrono.a")
set_target_properties(Boost_program_options PROPERTIES
        IMPORTED_LOCATION "${Boost_LIBRARY_DIRS}/libboost_program_options.a")

add_subdirectory(edi_parser)
