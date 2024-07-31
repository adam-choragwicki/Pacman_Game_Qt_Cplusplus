#pragma once

#include "abstract_ghost.h"
#include "pixmap_providers/blue_ghost_pixmap_provider.h"

class BlueGhost : public AbstractGhost
{
public:
    BlueGhost(BlueGhostPixmapProvider* pixmapProvider, ScaredGhostPixmapProvider* scaredGhostPixmapProvider);

private:
    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{3};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::UP};
    inline static const Coordinates STARTING_COORDINATES{265, 318};
};
