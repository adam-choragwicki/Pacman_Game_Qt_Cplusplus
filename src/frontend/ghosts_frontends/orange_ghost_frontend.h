#pragma once

#include "abstract_ghost_frontend.h"
#include "model/ghosts/orange_ghost.h"

class OrangeGhostFrontend : public AbstractGhostFrontend
{
public:
    explicit OrangeGhostFrontend(const OrangeGhost& orangeGhost);
};
