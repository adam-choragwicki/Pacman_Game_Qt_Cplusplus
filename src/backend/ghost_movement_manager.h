#pragma once

#include "abstract_movement_manager.h"

class GhostMovementManager : public AbstractMovementManager
{
public:
    void processMove(AbstractGhost& ghost, const Coordinates& pacmanCoordinates, const PathPoints& pathPoints);
    bool isGhostInsideStartingBox(const AbstractGhost& ghost);
    void basicMovementAI(AbstractGhost& ghost, const Coordinates& pacmanCoordinates);
    void moveUpAndDownInsideStartingBox(AbstractGhost& ghost);
    void moveOutOfStartingBox(AbstractGhost& ghost);
};
