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

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
        ${SOURCES_DIR}/main.cpp
        ${INCLUDES_DIR}/game.h ${SOURCES_DIR}/game.cpp
        ${INCLUDES_DIR}/common.h
        ${INCLUDES_DIR}/view/main_window.h ${SOURCES_DIR}/view/main_window.cpp
        ${INCLUDES_DIR}/view/score_display.h ${SOURCES_DIR}/view/score_display.cpp
        ${INCLUDES_DIR}/view/screen_text_display.h ${SOURCES_DIR}/view/screen_text_display.cpp
        ${INCLUDES_DIR}/controller.h ${SOURCES_DIR}/controller.cpp
        ${INCLUDES_DIR}/model.h ${SOURCES_DIR}/model.cpp
        ${INCLUDES_DIR}/movable_character.h ${SOURCES_DIR}/movable_character.cpp
        ${INCLUDES_DIR}/pacman.h ${SOURCES_DIR}/pacman.cpp
        ${INCLUDES_DIR}/ghosts/abstract_ghost.h ${SOURCES_DIR}/ghosts/abstract_ghost.cpp
        ${INCLUDES_DIR}/ghosts/blue_ghost.h ${SOURCES_DIR}/ghosts/blue_ghost.cpp
        ${INCLUDES_DIR}/ghosts/orange_ghost.h ${SOURCES_DIR}/ghosts/orange_ghost.cpp
        ${INCLUDES_DIR}/ghosts/purple_ghost.h ${SOURCES_DIR}/ghosts/purple_ghost.cpp
        ${INCLUDES_DIR}/ghosts/red_ghost.h ${SOURCES_DIR}/ghosts/red_ghost.cpp
        ${INCLUDES_DIR}/ball.h ${SOURCES_DIR}/ball.cpp
        ${INCLUDES_DIR}/game_map.h ${SOURCES_DIR}/game_map.cpp
        ${INCLUDES_DIR}/log_manager.h
        ${INCLUDES_DIR}/ball_items_manager.h ${SOURCES_DIR}/ball_items_manager.cpp
        ${INCLUDES_DIR}/coordinates.h ${SOURCES_DIR}/coordinates.cpp
        ${RESOURCE_FILES_DIR}/images.qrc src/ball.cpp inc/ball.h
        src/view/game_arena.cpp inc/view/game_arena.h)


add_library(libPacman ${SOURCE_FILES} src/view/pacman_frontend.cpp inc/view/pacman_frontend.h src/view/abstract_ghost_frontend.cpp inc/view/abstract_ghost_frontend.h src/view/blue_ghost_frontend.cpp inc/view/blue_ghost_frontend.h src/view/red_ghost_frontend.cpp inc/view/red_ghost_frontend.h src/view/purple_ghost_frontend.cpp inc/view/purple_ghost_frontend.h src/view/orange_ghost_frontend.cpp inc/view/orange_ghost_frontend.h src/view/ball_frontend.cpp inc/view/ball_frontend.h inc/score_manager.h src/screen_text_manager.cpp inc/screen_text_manager.h inc/collision_manager.cpp inc/collision_manager.h inc/view/gui_config.h src/speed_manager.cpp inc/speed_manager.h)
target_include_directories(libPacman PUBLIC ${INCLUDES_DIR})
target_link_libraries(libPacman Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(Pacman WIN32 ${SOURCE_FILES})
target_link_libraries(Pacman PRIVATE libPacman)

if (WIN32)
    set_target_properties(Pacman PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_windows)
elseif (UNIX)
    set_target_properties(Pacman PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_linux)
endif (WIN32)

add_subdirectory(tests)
