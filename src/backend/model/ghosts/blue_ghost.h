#pragma once

#include "abstract_ghost.h"

class BlueGhost : public AbstractGhost
{
public:
    BlueGhost();

private:
    inline static const std::array<QString, 8> IMAGES_URLS{":/ghosts/blue/ghost_blue_left_1.png", ":/ghosts/blue/ghost_blue_left_2.png", ":/ghosts/blue/ghost_blue_right_1.png", ":/ghosts/blue/ghost_blue_right_2.png",
                                                           ":/ghosts/blue/ghost_blue_up_1.png", ":/ghosts/blue/ghost_blue_up_2.png", ":/ghosts/blue/ghost_blue_down_1.png", ":/ghosts/blue/ghost_blue_down_2.png"};

    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{3};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::UP};
};
