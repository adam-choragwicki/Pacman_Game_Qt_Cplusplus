#pragma once

#include "abstract_ghost.h"

class RedGhost : public AbstractGhost
{
public:
    explicit RedGhost(std::shared_ptr<GhostPixmapProvider> pixmapProvider);

private:
    inline static const std::array<QString, 6> IMAGES_URLS{":/ghosts/red/ghost_red_right_1.png", ":/ghosts/red/ghost_red_right_2.png", ":/ghosts/red/ghost_red_up_1.png", ":/ghosts/red/ghost_red_up_2.png", ":/ghosts/red/ghost_red_down_1.png",
                                                           ":/ghosts/red/ghost_red_down_2.png"};

    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{0};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::LEFT};
    inline static const Coordinates STARTING_COORDINATES{307, 252};
};
