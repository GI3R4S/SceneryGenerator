cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

project(SceneryGenerator CXX)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(LevelGenerator)
add_subdirectory(LevelVisualisation)
add_subdirectory(Utils)