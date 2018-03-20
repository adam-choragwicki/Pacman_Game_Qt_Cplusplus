#pragma once

#include "model/pacman.h"
#include "path_points.h"
#include "model/ghosts/abstract_ghost.h"

#include <QRandomGenerator>

class AbstractMovementManager
{
public:
    void processMove(MovableCharacter& movableCharacter, const PathPoints& pathPoints);
    bool isPathPointValid(const Coordinates& coordinates, const PathPoints& pathPoints);
    void processNewDirectionRequest(MovableCharacter& movableCharacter, const PathPoints& pathPoints);
    [[nodiscard]] bool validateMove(const MovableCharacter& movableCharacter, const PathPoints& pathPoints) const;
    void checkAndProcessGameAreaBoundaryReach(MovableCharacter& movableCharacter);
    void move(MovableCharacter& movableCharacter, Direction direction);
};
