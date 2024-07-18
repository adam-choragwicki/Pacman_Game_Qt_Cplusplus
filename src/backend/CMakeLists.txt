set(SOURCE_FILES
        model/model.h model/model.cpp
        model/game_state_manager.cpp model/game_state_manager.h
        model/pacman.h model/pacman.cpp
        model/ghosts/abstract_ghost.h model/ghosts/abstract_ghost.cpp
        model/ghosts/blue_ghost.h model/ghosts/blue_ghost.cpp
        model/ghosts/orange_ghost.h model/ghosts/orange_ghost.cpp
        model/ghosts/purple_ghost.h model/ghosts/purple_ghost.cpp
        model/ghosts/red_ghost.h model/ghosts/red_ghost.cpp
        model/ball_items_manager.h model/ball_items_manager.cpp
        model/timing_manager.h model/pacman_timing_manager.cpp model/ghost_timing_manager.cpp
        common.h
        movable_character.h movable_character.cpp
        path_points.h path_points.cpp
        log_manager.h
        coordinates.h coordinates.cpp
        score_manager.h
        screen_text_manager.cpp screen_text_manager.h
        collision_manager.cpp collision_manager.h
        config.h
        movement_manager.cpp movement_manager.h
        pacman_movement_manager.cpp
        ghost_movement_manager.cpp
        directional_offset.h

        model/balls/abstract_ball.cpp model/balls/abstract_ball.h
        model/balls/foodball.cpp model/balls/foodball.h
        model/balls/powerball.cpp model/balls/powerball.h)

add_library(lib${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC Qt${QT_VERSION_MAJOR}::Core)
