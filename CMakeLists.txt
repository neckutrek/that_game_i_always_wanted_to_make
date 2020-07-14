cmake_minimum_required(VERSION 3.0)

project(that_game)

find_package(sdl2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GTest REQUIRED)

set( THIRD_PARTY_INCLUDE_DIR        ${SDL2_INCLUDE_DIRS} ${GTEST_INCLUDE_DIR} )
set( EXTERNAL_INCLUDE_DIR           ${PROJECT_SOURCE_DIR}/include )
set( INTERNAL_INCLUDE_DIR           ${PROJECT_SOURCE_DIR}/src )

set( BINARY_OUTPUT_DIR              ${CMAKE_SOURCE_DIR}/bin )
set( TEST_BINARY_OUTPUT_DIR         ${CMAKE_SOURCE_DIR}/bin/test )

set( CMAKE_LIBRARY_PATH             ${BINARY_OUTPUT_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_OUTPUT_DIR} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wextra -Wpedantic -Wall -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

enable_testing()

add_subdirectory("${PROJECT_SOURCE_DIR}/src")