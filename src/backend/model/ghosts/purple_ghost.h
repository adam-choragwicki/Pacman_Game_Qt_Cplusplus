#pragma once

#include "abstract_ghost.h"

class PurpleGhost : public AbstractGhost
{
public:
    PurpleGhost();

private:
    inline static const std::array<QString, 8> IMAGES_URLS{":/ghosts/purple/ghost_purple_left_1.png", ":/ghosts/purple/ghost_purple_left_2.png", ":/ghosts/purple/ghost_purple_right_1.png", ":/ghosts/purple/ghost_purple_right_2.png",
                                                           ":/ghosts/purple/ghost_purple_up_1.png", ":/ghosts/purple/ghost_purple_up_2.png", ":/ghosts/purple/ghost_purple_down_1.png", ":/ghosts/purple/ghost_purple_down_2.png"};

    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{1};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::UP};
};
