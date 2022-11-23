cmake_minimum_required(VERSION 3.12)
project(SceneryGenerator.LevelGenerator.Test.Unit CXX)

find_package(GTest)

set(TEST_SOURCES BasicSceneryGeneratorTest.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME}
    SceneryGenerator.LevelGenerator
    gtest::gtest
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
      ../../src    
)
add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)