#pragma once

#include "abstract_ghost_frontend.h"
#include "model/ghosts/blue_ghost.h"

class BlueGhostFrontend : public AbstractGhostFrontend
{
public:
    explicit BlueGhostFrontend(const BlueGhost& blueGhost);
};
