#pragma once

#include "abstract_ghost.h"
#include "pixmap_providers/orange_ghost_pixmap_provider.h"

class OrangeGhost : public AbstractGhost
{
public:
    OrangeGhost(OrangeGhostPixmapProvider* pixmapProvider, ScaredGhostPixmapProvider* scaredGhostPixmapProvider);

private:
    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{2};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::UP};
    inline static const Coordinates STARTING_COORDINATES{349, 318};
};
