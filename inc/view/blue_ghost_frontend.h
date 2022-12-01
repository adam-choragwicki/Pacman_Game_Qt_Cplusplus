#pragma once

#include "abstract_ghost_frontend.h"
#include "ghosts/blue_ghost.h"

class BlueGhostFrontend : public AbstractGhostFrontend
{
public:
    explicit BlueGhostFrontend(BlueGhost* blueGhost);

private:
    inline static const std::array<std::string, 12> IMAGES_URLS{":/ghost/images/ghost/ghost_blue_left_1.png", ":/ghost/images/ghost/ghost_blue_left_2.png",
                                                                ":/ghost/images/ghost/ghost_blue_right_1.png", ":/ghost/images/ghost/ghost_blue_right_2.png",
                                                                ":/ghost/images/ghost/ghost_blue_up_1.png", ":/ghost/images/ghost/ghost_blue_up_2.png", ":/ghost/images/ghost/ghost_blue_down_1.png",
                                                                ":/ghost/images/ghost/ghost_blue_down_2.png",

                                                                ":/ghost/images/ghost/ghost_scared_blue_1.png", ":/ghost/images/ghost/ghost_scared_blue_2.png",
                                                                ":/ghost/images/ghost/ghost_scared_white_1.png", ":/ghost/images/ghost/ghost_scared_white_2.png",};
};
