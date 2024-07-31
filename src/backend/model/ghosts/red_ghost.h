#pragma once

#include "abstract_ghost.h"
#include "pixmap_providers/red_ghost_pixmap_provider.h"

class RedGhost : public AbstractGhost
{
public:
    explicit RedGhost(RedGhostPixmapProvider* pixmapProvider, ScaredGhostPixmapProvider* scaredGhostPixmapProvider);

private:
    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{0};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::LEFT};
    inline static const Coordinates STARTING_COORDINATES{307, 252};
};
