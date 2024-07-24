#pragma once

#include "abstract_ghost.h"

class OrangeGhost : public AbstractGhost
{
public:
    OrangeGhost();

private:
    inline static const std::array<QString, 8> IMAGES_URLS{":/ghost/ghost_orange_left_1.png", ":/ghost/ghost_orange_left_2.png", ":/ghost/ghost_orange_right_1.png", ":/ghost/ghost_orange_right_2.png", ":/ghost/ghost_orange_up_1.png",
                                                           ":/ghost/ghost_orange_up_2.png", ":/ghost/ghost_orange_down_1.png", ":/ghost/ghost_orange_down_2.png"};
};
