#pragma once

#include "abstract_ghost_frontend.h"
#include "ghosts/purple_ghost.h"

class PurpleGhostFrontend : public AbstractGhostFrontend
{
public:
    explicit PurpleGhostFrontend(PurpleGhost* purpleGhost);

private:
    inline static const std::array<std::string, 12> IMAGES_URLS{":/ghost/images/ghost/ghost_purple_left_1.png", ":/ghost/images/ghost/ghost_purple_left_2.png",
                                                             ":/ghost/images/ghost/ghost_purple_right_1.png", ":/ghost/images/ghost/ghost_purple_right_2.png",
                                                             ":/ghost/images/ghost/ghost_purple_up_1.png", ":/ghost/images/ghost/ghost_purple_up_2.png", ":/ghost/images/ghost/ghost_purple_down_1.png",
                                                             ":/ghost/images/ghost/ghost_purple_down_2.png",

                                                             ":/ghost/images/ghost/ghost_scared_blue_1.png", ":/ghost/images/ghost/ghost_scared_blue_2.png",
                                                             ":/ghost/images/ghost/ghost_scared_white_1.png", ":/ghost/images/ghost/ghost_scared_white_2.png",};
};
