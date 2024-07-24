#pragma once

#include "abstract_ghost.h"

class RedGhost : public AbstractGhost
{
public:
    RedGhost();

private:
    inline static const std::array<QString, 8> IMAGES_URLS{":/ghost/ghost_red_right_1.png", ":/ghost/ghost_red_right_2.png", ":/ghost/ghost_red_up_1.png", ":/ghost/ghost_red_up_2.png", ":/ghost/ghost_red_down_1.png", ":/ghost/ghost_red_down_2.png",
                                                           ":/ghost/ghost_red_left_1.png", ":/ghost/ghost_red_left_2.png"};
};
