set(SOURCE_FILES
        main_window.h main_window.cpp
        graphics_view.h graphics_view.cpp
        game_arena.cpp game_arena.h
        images_urls.h
        gui_config.h)

# Create the frontend library
add_library(lib${PROJECT_NAME}Frontend ${SOURCE_FILES})

# Include directories for frontend
target_include_directories(lib${PROJECT_NAME}Frontend PUBLIC . ${BACKEND_DIR})

# Link spdlog and Qt Widgets to frontend
target_link_libraries(lib${PROJECT_NAME}Frontend PUBLIC spdlog::spdlog Qt${QT_VERSION_MAJOR}::Widgets)
