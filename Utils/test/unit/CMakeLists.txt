cmake_minimum_required(VERSION 3.12)
project(SceneryGenerator.Utils.Test.Unit CXX)

find_package(GTest)

set(TEST_SOURCES RandomNumberGeneratorTest.cpp)

add_executable(${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} 
    SceneryGenerator.Utils
    gtest::gtest
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)