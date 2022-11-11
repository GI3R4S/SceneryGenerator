cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)

project(SceneryGenerator.LevelVisualisation CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC SceneryGenerator.LevelGenerator)
target_link_libraries(${PROJECT_NAME} PUBLIC SceneryGenerator.Utils)

