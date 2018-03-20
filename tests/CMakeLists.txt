set(TEST_SOURCES
        src/main.cpp
        src/pacman_test.cpp
        src/ghost_test.cpp)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest lib${PROJECT_NAME}Backend Qt${QT_VERSION_MAJOR}::Widgets)
