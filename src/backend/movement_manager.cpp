#include "movement_manager.h"
#include "directional_offset.h"

bool MovementManager::isPathPointValid(const Coordinates& coordinates, const PathPoints& pathPoints)
{
    return pathPoints.isPathPointValid(coordinates);
}

void MovementManager::processNewDirectionRequest(MovableCharacter& movableCharacter, const PathPoints& pathPoints)
{
    const Direction direction = movableCharacter.getDirection();
    const Direction nextDirection = movableCharacter.getNextDirection();
    const Coordinates coordinates = movableCharacter.getCoordinates();

    if(nextDirection != direction)
    {
        DirectionalOffset directionalOffset(nextDirection);

        const Coordinates newCoordinates = coordinates + directionalOffset.toStdPair();

        if(isPathPointValid(newCoordinates, pathPoints))
        {
            movableCharacter.setDirection(nextDirection);
        }
    }
}

bool MovementManager::validateMove(const MovableCharacter& movableCharacter, const PathPoints& pathPoints) const
{
    const Direction direction = movableCharacter.getDirection();
    const Coordinates coordinates = movableCharacter.getCoordinates();

    DirectionalOffset directionalOffset(direction);
    return pathPoints.isPathPointValid(coordinates + directionalOffset.toStdPair());
}

void MovementManager::checkAndProcessGameAreaBoundaryReach(MovableCharacter& movableCharacter)
{
    const Coordinates coordinates = movableCharacter.getCoordinates();

    const int LEFT_EDGE_X = 0;
    const int RIGHT_EDGE_X = 614;
    const int HORIZONTAL_CENTER_LINE_Y = 318;

    if(coordinates.x_ <= LEFT_EDGE_X)
    {
        movableCharacter.moveTo({RIGHT_EDGE_X - 1, HORIZONTAL_CENTER_LINE_Y});
    }

    if(coordinates.x_ >= RIGHT_EDGE_X)
    {
        movableCharacter.moveTo({LEFT_EDGE_X + 1, HORIZONTAL_CENTER_LINE_Y});
    }
}

void MovementManager::processMove(MovableCharacter& movableCharacter, const PathPoints& pathPoints)
{
    processNewDirectionRequest(movableCharacter, pathPoints);

    if(validateMove(movableCharacter, pathPoints))
    {
        move(movableCharacter, movableCharacter.getDirection());
        movableCharacter.setMoving(true);
        checkAndProcessGameAreaBoundaryReach(movableCharacter);
        movableCharacter.advanceAnimation();
    }
    else
    {
        movableCharacter.setMoving(false);
    }
}

void MovementManager::move(MovableCharacter& movableCharacter, Direction direction)
{
    DirectionalOffset directionalOffset(direction);
    movableCharacter.moveBy(directionalOffset.toStdPair());
}
