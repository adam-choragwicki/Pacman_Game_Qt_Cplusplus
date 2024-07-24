#pragma once

#include "abstract_ghost.h"

class BlueGhost : public AbstractGhost
{
public:
    BlueGhost();

private:
    inline static const std::array<QString, 8> IMAGES_URLS{":/ghost/ghost_blue_left_1.png", ":/ghost/ghost_blue_left_2.png", ":/ghost/ghost_blue_right_1.png", ":/ghost/ghost_blue_right_2.png", ":/ghost/ghost_blue_up_1.png",
                                                           ":/ghost/ghost_blue_up_2.png", ":/ghost/ghost_blue_down_1.png", ":/ghost/ghost_blue_down_2.png"};
};
