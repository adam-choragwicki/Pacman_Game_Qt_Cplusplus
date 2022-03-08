cmake_minimum_required(VERSION 3.10)

project(Pacman LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(INCLUDES_DIR ${PROJECT_ROOT}/inc)
set(SOURCES_DIR ${PROJECT_ROOT}/src)
set(UI_FORMS_DIR ${PROJECT_ROOT}/ui_forms)
set(RESOURCE_FILES_DIR ${PROJECT_ROOT}/resource_files)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
    ${SOURCES_DIR}/main.cpp
    ${INCLUDES_DIR}/common.h
    ${INCLUDES_DIR}/game_window.h ${SOURCES_DIR}/game_window.cpp ${UI_FORMS_DIR}/game_window.ui
    ${INCLUDES_DIR}/game_engine.h ${SOURCES_DIR}/game_engine.cpp
    ${INCLUDES_DIR}/movable_character_interface.h ${SOURCES_DIR}/movable_character_interface.cpp
    ${INCLUDES_DIR}/pacman.h ${SOURCES_DIR}/pacman.cpp
    ${INCLUDES_DIR}/ghost_base.h ${SOURCES_DIR}/ghost_base.cpp
    ${INCLUDES_DIR}/ghost_blue.h ${SOURCES_DIR}/ghost_blue.cpp
    ${INCLUDES_DIR}/ghost_orange.h ${SOURCES_DIR}/ghost_orange.cpp
    ${INCLUDES_DIR}/ghost_purple.h ${SOURCES_DIR}/ghost_purple.cpp
    ${INCLUDES_DIR}/ghost_red.h ${SOURCES_DIR}/ghost_red.cpp
    ${INCLUDES_DIR}/foodball.h ${SOURCES_DIR}/foodball.cpp
    ${INCLUDES_DIR}/powerball.h ${SOURCES_DIR}/powerball.cpp
    ${INCLUDES_DIR}/game_map.h ${SOURCES_DIR}/game_map.cpp
    ${INCLUDES_DIR}/drawer.h ${SOURCES_DIR}/drawer.cpp
    ${INCLUDES_DIR}/score_display.h ${SOURCES_DIR}/score_display.cpp
    ${INCLUDES_DIR}/screen_text_display.h ${SOURCES_DIR}/screen_text_display.cpp
    ${RESOURCE_FILES_DIR}/images.qrc
)

add_library(libPacman ${SOURCE_FILES})
target_include_directories(libPacman PUBLIC ${INCLUDES_DIR})
target_link_libraries(libPacman Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(Pacman WIN32 ${SOURCE_FILES})
target_link_libraries(Pacman PRIVATE libPacman)

if(WIN32)
    set_target_properties(Pacman PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_windows)
elseif(UNIX)
    set_target_properties(Pacman PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_linux)
endif(WIN32)

add_subdirectory(tests)
