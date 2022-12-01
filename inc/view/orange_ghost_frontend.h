#pragma once

#include "abstract_ghost_frontend.h"
#include "ghosts/orange_ghost.h"

class OrangeGhostFrontend : public AbstractGhostFrontend
{
public:
    explicit OrangeGhostFrontend(OrangeGhost* orangeGhost);

private:
    inline static const std::array<std::string, 12> IMAGES_URLS{":/ghost/images/ghost/ghost_orange_left_1.png", ":/ghost/images/ghost/ghost_orange_left_2.png",
                                                                ":/ghost/images/ghost/ghost_orange_right_1.png", ":/ghost/images/ghost/ghost_orange_right_2.png",
                                                                ":/ghost/images/ghost/ghost_orange_up_1.png", ":/ghost/images/ghost/ghost_orange_up_2.png",
                                                                ":/ghost/images/ghost/ghost_orange_down_1.png", ":/ghost/images/ghost/ghost_orange_down_2.png",

                                                                ":/ghost/images/ghost/ghost_scared_blue_1.png", ":/ghost/images/ghost/ghost_scared_blue_2.png",
                                                                ":/ghost/images/ghost/ghost_scared_white_1.png", ":/ghost/images/ghost/ghost_scared_white_2.png",};
};
