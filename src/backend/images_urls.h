#pragma once

#include <array>
#include <string>

namespace PacmanImages
{
    const std::array<std::string, 16> IMAGES_URLS{":/pacman/pacman_left_close.png", ":/pacman/pacman_left_open_1.png", ":/pacman/pacman_left_open_2.png", ":/pacman/pacman_left_open_3.png",

                                                  ":/pacman/pacman_right_close.png", ":/pacman/pacman_right_open_1.png", ":/pacman/pacman_right_open_2.png", ":/pacman/pacman_right_open_3.png",

                                                  ":/pacman/pacman_up_close.png", ":/pacman/pacman_up_open_1.png", ":/pacman/pacman_up_open_2.png", ":/pacman/pacman_up_open_3.png",

                                                  ":/pacman/pacman_down_close.png", ":/pacman/pacman_down_open_1.png", ":/pacman/pacman_down_open_2.png", ":/pacman/pacman_down_open_3.png"};
}

namespace BlueGhostImages
{
    const std::array<std::string, 12> IMAGES_URLS{":/ghost/ghost_blue_left_1.png", ":/ghost/ghost_blue_left_2.png", ":/ghost/ghost_blue_right_1.png", ":/ghost/ghost_blue_right_2.png", ":/ghost/ghost_blue_up_1.png", ":/ghost/ghost_blue_up_2.png",
                                                  ":/ghost/ghost_blue_down_1.png", ":/ghost/ghost_blue_down_2.png",

                                                  ":/ghost/ghost_scared_blue_1.png", ":/ghost/ghost_scared_blue_2.png", ":/ghost/ghost_scared_white_1.png", ":/ghost/ghost_scared_white_2.png",};
}

namespace OrangeGhostImages
{
    const std::array<std::string, 12> IMAGES_URLS{":/ghost/ghost_orange_left_1.png", ":/ghost/ghost_orange_left_2.png", ":/ghost/ghost_orange_right_1.png", ":/ghost/ghost_orange_right_2.png", ":/ghost/ghost_orange_up_1.png",
                                                  ":/ghost/ghost_orange_up_2.png", ":/ghost/ghost_orange_down_1.png", ":/ghost/ghost_orange_down_2.png",

                                                  ":/ghost/ghost_scared_blue_1.png", ":/ghost/ghost_scared_blue_2.png", ":/ghost/ghost_scared_white_1.png", ":/ghost/ghost_scared_white_2.png",};
}

namespace PurpleGhostImages
{
    const std::array<std::string, 12> IMAGES_URLS{":/ghost/ghost_purple_left_1.png", ":/ghost/ghost_purple_left_2.png", ":/ghost/ghost_purple_right_1.png", ":/ghost/ghost_purple_right_2.png", ":/ghost/ghost_purple_up_1.png",
                                                  ":/ghost/ghost_purple_up_2.png", ":/ghost/ghost_purple_down_1.png", ":/ghost/ghost_purple_down_2.png",

                                                  ":/ghost/ghost_scared_blue_1.png", ":/ghost/ghost_scared_blue_2.png", ":/ghost/ghost_scared_white_1.png", ":/ghost/ghost_scared_white_2.png",};

}

namespace RedGhostImages
{
    const std::array<std::string, 12> IMAGES_URLS{":/ghost/ghost_red_right_1.png", ":/ghost/ghost_red_right_2.png", ":/ghost/ghost_red_up_1.png", ":/ghost/ghost_red_up_2.png", ":/ghost/ghost_red_down_1.png", ":/ghost/ghost_red_down_2.png",
                                                  ":/ghost/ghost_red_left_1.png", ":/ghost/ghost_red_left_2.png",

                                                  ":/ghost/ghost_scared_blue_1.png", ":/ghost/ghost_scared_blue_2.png", ":/ghost/ghost_scared_white_1.png", ":/ghost/ghost_scared_white_2.png"};
}
