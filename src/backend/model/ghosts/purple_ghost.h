#pragma once

#include "abstract_ghost.h"
#include "pixmap_providers/purple_ghost_pixmap_provider.h"

class PurpleGhost : public AbstractGhost
{
public:
    explicit PurpleGhost(PurpleGhostPixmapProvider* pixmapProvider, ScaredGhostPixmapProvider* scaredGhostPixmapProvider);

private:
    inline static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{1};
    inline static constexpr Direction INITIAL_DIRECTION{Direction::UP};
    inline static const Coordinates STARTING_COORDINATES{307, 318};
};
