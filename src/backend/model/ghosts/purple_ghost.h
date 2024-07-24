#pragma once

#include "abstract_ghost.h"

class PurpleGhost : public AbstractGhost
{
public:
    PurpleGhost();

private:
    inline static const std::array<QString, 8> IMAGES_URLS{":/ghost/ghost_purple_left_1.png", ":/ghost/ghost_purple_left_2.png", ":/ghost/ghost_purple_right_1.png", ":/ghost/ghost_purple_right_2.png", ":/ghost/ghost_purple_up_1.png",
                                                           ":/ghost/ghost_purple_up_2.png", ":/ghost/ghost_purple_down_1.png", ":/ghost/ghost_purple_down_2.png"};
};
