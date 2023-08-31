#pragma once

#include "abstract_ghost_frontend.h"
#include "model/ghosts/purple_ghost.h"

class PurpleGhostFrontend : public AbstractGhostFrontend
{
public:
    explicit PurpleGhostFrontend(const PurpleGhost& purpleGhost);
};
