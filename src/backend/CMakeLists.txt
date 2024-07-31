set(SOURCE_FILES
        model/model.h model/model.cpp

        game_loop.cpp game_loop.h
        input_handler.cpp input_handler.h
        game_manager.cpp game_manager.h

        model/pacman.h model/pacman.cpp
        model/ghosts/abstract_ghost.h model/ghosts/abstract_ghost.cpp
        model/ghosts/blue_ghost.h model/ghosts/blue_ghost.cpp
        model/ghosts/orange_ghost.h model/ghosts/orange_ghost.cpp
        model/ghosts/purple_ghost.h model/ghosts/purple_ghost.cpp
        model/ghosts/red_ghost.h model/ghosts/red_ghost.cpp

        model/ghost_timing_manager.cpp model/ghost_timing_manager.h

        model/pellets_manager.h model/pellets_manager.cpp
        model/pellets/abstract_pellet.cpp model/pellets/abstract_pellet.h
        model/pellets/standard_pellet.h
        model/pellets/power_pellet.h

        model/what_to_draw_manager.h

        model/graphics_scene.cpp model/graphics_scene.h

        common.h

        movable_character.h movable_character.cpp
        path_points.h path_points.cpp
        coordinates.h coordinates.cpp
        score_manager.h
        collision_manager.cpp collision_manager.h

        abstract_movement_manager.cpp abstract_movement_manager.h
        pacman_movement_manager.cpp pacman_movement_manager.h
        ghost_movement_manager.cpp ghost_movement_manager.h

        directional_offset.h

        screen_text_display.h screen_text_display.cpp

        custom_graphics_item.cpp custom_graphics_item.h
        id_generator.h

        score_display.h score_display.cpp
        game_manager.cpp game_manager.h

        pixmap_loader.h
        pixmap_manager.h

        pixmap_providers/pacman_pixmap_provider.cpp pixmap_providers/pacman_pixmap_provider.h
        pixmap_providers/abstract_ghost_pixmap_provider.cpp pixmap_providers/abstract_ghost_pixmap_provider.h
        pixmap_providers/scared_ghost_pixmap_provider.cpp pixmap_providers/scared_ghost_pixmap_provider.h pixmap_providers/red_ghost_pixmap_provider.cpp pixmap_providers/red_ghost_pixmap_provider.h pixmap_providers/purple_ghost_pixmap_provider.cpp pixmap_providers/purple_ghost_pixmap_provider.h pixmap_providers/blue_ghost_pixmap_provider.cpp pixmap_providers/blue_ghost_pixmap_provider.h pixmap_providers/orange_ghost_pixmap_provider.cpp pixmap_providers/orange_ghost_pixmap_provider.h)

# Create the backend library
add_library(lib${PROJECT_NAME}Backend ${SOURCE_FILES})

# Include current directory for backend library
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)

# Link Qt Core library to backend
target_link_libraries(lib${PROJECT_NAME}Backend PRIVATE spdlog::spdlog Qt${QT_VERSION_MAJOR}::Core)
