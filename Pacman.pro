#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T21:16:16
#
#-------------------------------------------------

QT += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = ../../Pacman_Game_Single_Player_Qt_Cplusplus/executable_windows/Pacman
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/drawer.cpp \
    src/game_engine.cpp \
    src/game_map.cpp \
    src/game_window.cpp \
    src/ghost_base.cpp \
    src/ghost_blue.cpp \
    src/ghost_orange.cpp \
    src/ghost_purple.cpp \
    src/ghost_red.cpp \
    src/movable_character_interface.cpp \
    src/pacman.cpp \
    src/foodball.cpp \
    src/powerball.cpp \
    src/sounds.cpp \
    src/score_display.cpp \
    src/screen_text_display.cpp \
    src/log_manager.cpp

HEADERS += \
    inc/common.h \
    inc/drawer.h \
    inc/game_engine.h \
    inc/game_map.h \
    inc/game_window.h \
    inc/ghost_base.h \
    inc/ghost_blue.h \
    inc/ghost_orange.h \
    inc/ghost_purple.h \
    inc/ghost_red.h \
    inc/movable_character_interface.h \
    inc/pacman.h \
    inc/foodball.h \
    inc/powerball.h \
    inc/sounds.h \
    inc/score_display.h \
    inc/screen_text_display.h \
    inc/log_manager.h

FORMS += \
    ui_forms/game_window.ui

RESOURCES += \
    resource_files/images.qrc \
    resource_files/sounds.qrc

DISTFILES +=
