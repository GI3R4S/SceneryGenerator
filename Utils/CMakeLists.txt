cmake_minimum_required(VERSION 3.12)

project(SceneryGenerator.Utils CXX C)
set(CMAKE_CXX_STANDARD 20)

set(PUBLIC_HEADERS
    include/GeometryUtils.hpp
    include/RandomNumberGenerator.hpp
)

set(IMPLEMENTATION_HEADERS
)

set(IMPLEMENTATION_SOURCES
    src/GeometryUtils.cpp
    src/RandomNumberGenerator.cpp
)

add_library(${PROJECT_NAME} STATIC
    ${PUBLIC_HEADERS}
    ${IMPLEMENTATION_HEADERS}
    ${IMPLEMENTATION_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include
)

enable_testing()

add_subdirectory(test)
