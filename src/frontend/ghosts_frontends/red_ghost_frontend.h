#pragma once

#include "abstract_ghost_frontend.h"
#include "model/ghosts/red_ghost.h"

class RedGhostFrontend : public AbstractGhostFrontend
{
public:
    explicit RedGhostFrontend(const RedGhost& redGhost);
};
