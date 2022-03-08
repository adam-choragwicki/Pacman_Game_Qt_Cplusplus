cmake_minimum_required(VERSION 3.10)

project(MinesweeperTest LANGUAGES CXX)

set(TEST_SOURCES
    src/main.cpp
    src/common_test_fixture.cpp)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(PacmanTest_run ${TEST_SOURCES} ${RESOURCE_FILES_DIR}/images.qrc)
target_include_directories(PacmanTest_run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(PacmanTest_run gtest gtest_main libPacman)
