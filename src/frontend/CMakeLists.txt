set(SOURCE_FILES
        main_window.h main_window.cpp
        graphics_view.h graphics_view.cpp
        score_display.h
        game_arena.cpp game_arena.h
        pacman_frontend.cpp pacman_frontend.h
        ghosts_frontends/abstract_ghost_frontend.cpp ghosts_frontends/abstract_ghost_frontend.h
        ghosts_frontends/blue_ghost_frontend.cpp ghosts_frontends/blue_ghost_frontend.h
        ghosts_frontends/red_ghost_frontend.cpp ghosts_frontends/red_ghost_frontend.h
        ghosts_frontends/purple_ghost_frontend.cpp ghosts_frontends/purple_ghost_frontend.h
        ghosts_frontends/orange_ghost_frontend.cpp ghosts_frontends/orange_ghost_frontend.h
        images_urls.h
        gui_config.h)

add_library(lib${PROJECT_NAME}Frontend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Frontend PUBLIC . ${BACKEND_DIR})
target_link_libraries(lib${PROJECT_NAME}Frontend PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
