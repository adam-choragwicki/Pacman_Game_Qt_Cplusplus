#include "movement_manager.h"
#include "directional_offset.h"

bool GhostMovementManager::isGhostInsideStartingBox(const AbstractGhost& ghost)
{
    const int STARTING_BOX_LEFT_EDGE_X = 209;
    const int STARTING_BOX_RIGHT_EDGE_X = 406;
    const int STARTING_BOX_TOP_EDGE_Y = 252;
    const int STARTING_BOX_BOTTOM_EDGE_Y = 384;

    const Coordinates coordinates = ghost.getCoordinates();

    return (coordinates.x_ > STARTING_BOX_LEFT_EDGE_X && coordinates.x_ < STARTING_BOX_RIGHT_EDGE_X) && (coordinates.y_ > STARTING_BOX_TOP_EDGE_Y && coordinates.y_ < STARTING_BOX_BOTTOM_EDGE_Y);
}

void GhostMovementManager::processMove(AbstractGhost& ghost, const Coordinates& pacmanCoordinates, const PathPoints& pathPoints)
{
    basicMovementAI(ghost, pacmanCoordinates);
    MovementManager::processMove(ghost, pathPoints);
}

void GhostMovementManager::basicMovementAI(AbstractGhost& ghost, const Coordinates& pacmanCoordinates)
{
    const int GHOST_X = ghost.getCoordinates().x_;
    const int GHOST_Y = ghost.getCoordinates().y_;

    const int PACMAN_X = pacmanCoordinates.x_;
    const int PACMAN_Y = pacmanCoordinates.y_;

    const Direction direction = ghost.getDirection();

    if(ghost.isMoving())
    {
        if((direction == Direction::RIGHT && GHOST_Y < PACMAN_Y) || (direction == Direction::LEFT && GHOST_Y > PACMAN_Y))
        {
            if(direction == Direction::LEFT && GHOST_Y > PACMAN_Y)
            {
                ghost.setNextDirection(Direction::UP);
            }
            else if(direction == Direction::RIGHT && GHOST_Y < PACMAN_Y)
            {
                ghost.setNextDirection(Direction::DOWN);
            }
        }
        else if((direction == Direction::DOWN && GHOST_X < PACMAN_X) || (direction == Direction::UP && GHOST_X > PACMAN_X))
        {
            if(direction == Direction::UP && GHOST_X > PACMAN_X)
            {
                ghost.setNextDirection(Direction::LEFT);
            }
            else if(direction == Direction::DOWN && GHOST_X < PACMAN_X)
            {
                ghost.setNextDirection(Direction::RIGHT);
            }
        }
    }
    else
    {
        //TODO choose directly from container
        ghost.setDirection(static_cast<Direction>(QRandomGenerator::global()->bounded(1, 4)));
    }
}

void GhostMovementManager::moveInsideStartingBox(AbstractGhost& ghost)
{
    //TODO make it part of standard movement process
    const int CENTER_Y = 318;
    const int MAX_VERTICAL_MOVEMENT_OFFSET = 15;
    constexpr int MIN_Y_AFTER_OFFSET = CENTER_Y - MAX_VERTICAL_MOVEMENT_OFFSET;
    constexpr int MAX_Y_AFTER_OFFSET = CENTER_Y + MAX_VERTICAL_MOVEMENT_OFFSET;

    const Coordinates coordinates_ = ghost.getCoordinates();
    Direction direction = ghost.getDirection();

    if((coordinates_.y_ == MIN_Y_AFTER_OFFSET) || (coordinates_.y_ == MAX_Y_AFTER_OFFSET))
    {
        if(direction == Direction::UP)
        {
            ghost.setDirection(Direction::DOWN);
        }
        else if(direction == Direction::DOWN)
        {
            ghost.setDirection(Direction::UP);
        }
    }

    VerticalDirectionalOffset verticalDirectionalOffset(ghost.getDirection());
    ghost.moveCharacterBy(verticalDirectionalOffset.toStdPair());
}

void GhostMovementManager::moveOutOfStartingBox(AbstractGhost& ghost)
{
    //TODO make it part of standard movement process
    const int CENTER_X = 307;
    const Coordinates coordinates_ = ghost.getCoordinates();

    DirectionalOffset directionalOffset;

    if(coordinates_.x_ > CENTER_X)
    {
        directionalOffset = Direction::LEFT;
    }
    else if(coordinates_.x_ < CENTER_X)
    {
        directionalOffset = Direction::RIGHT;
    }
    else
    {
        directionalOffset = Direction::UP;
    }

    ghost.moveCharacterBy(directionalOffset.toStdPair());
}
