cmake_minimum_required(VERSION 3.12)

project(LevelGenerator CXX C)
set(CMAKE_CXX_STANDARD 20)

set(PUBLIC_HEADERS
    include/BasicLevelGenerator.hpp
    include/LevelData.hpp
    include/LevelGenerator.hpp
)

set(IMPLEMENTATION_HEADERS
    src/BasicLevelGeneratorImpl.hpp
)

set(IMPLEMENTATION_SOURCES
    src/BasicLevelGenerator.cpp
    src/BasicLevelGeneratorImpl.cpp
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
