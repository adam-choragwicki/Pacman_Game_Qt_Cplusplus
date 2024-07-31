#pragma once

#include "abstract_ghost.h"

class OrangeGhost : public AbstractGhost
{
public:
    OrangeGhost(std::shared_ptr<GhostPixmapProvider> pixmapProvider);

private:
    inline static const std::array<QString, 6> IMAGES_URLS{":/ghosts/orange/ghost_orange_right_1.png", ":/ghosts/orange/ghost_orange_right_2.png", ":/ghosts/orange/ghost_orange_up_1.png", ":/ghosts/orange/ghost_orange_up_2.png",
                                                           ":/ghosts/orange/ghost_orange_down_1.png", ":/ghosts/orange/ghost_orange_down_2.png"};

    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{2};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::UP};
    inline static const Coordinates STARTING_COORDINATES{349, 318};
};
