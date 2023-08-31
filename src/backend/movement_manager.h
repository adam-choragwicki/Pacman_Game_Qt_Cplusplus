#pragma once

#include "model/pacman.h"
#include "path_points.h"
#include "model/ghosts/abstract_ghost.h"

#include <QRandomGenerator>

class MovementManager
{
public:
    void processMove(MovableCharacter& movableCharacter, const PathPoints& pathPoints);
    bool isPathPointValid(const Coordinates& coordinates, const PathPoints& pathPoints);
    void processNewDirectionRequest(MovableCharacter& movableCharacter, const PathPoints& pathPoints);
    [[nodiscard]] bool validateMove(const MovableCharacter& movableCharacter, const PathPoints& pathPoints) const;
    void checkAndProcessGameAreaBoundaryReach(MovableCharacter& movableCharacter);
    void move(MovableCharacter& movableCharacter, Direction direction);
};

class PacmanMovementManager : public MovementManager
{
public:
    void processMove(Pacman& pacman, const PathPoints& pathPoints);
};

class GhostMovementManager : public MovementManager
{
public:
    void processMove(AbstractGhost& ghost, const Coordinates& pacmanCoordinates, const PathPoints& pathPoints);
    bool isGhostInsideStartingBox(const AbstractGhost& ghost);
    void basicMovementAI(AbstractGhost& ghost, const Coordinates& pacmanCoordinates);
    void moveInsideStartingBox(AbstractGhost& ghost);
    void moveOutOfStartingBox(AbstractGhost& ghost);
};
