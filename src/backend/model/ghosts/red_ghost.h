#pragma once

#include "abstract_ghost.h"

class RedGhostPixmapProvider;

class RedGhost : public AbstractGhost
{
public:
    explicit RedGhost(RedGhostPixmapProvider* pixmapProvider);

private:
    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{0};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::LEFT};
    inline static const Coordinates STARTING_COORDINATES{307, 252};
};
