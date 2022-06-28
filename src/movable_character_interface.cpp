#include "movable_character_interface.h"
#include "game_map.h"

MovableCharacterInterface::MovableCharacterInterface(const Coordinates& coordinates, Direction initialDirection, const GameMap& gameMap) :
        coordinates_(coordinates), direction_(initialDirection), gameMap_(gameMap)
{
    nextDirection_ = Direction::none;
    MovableCharacterInterface::reset();
}

void MovableCharacterInterface::reset()
{
    moving_ = false;
    nextDirection_ = Direction::none;
    animationState_ = 0;
}

void MovableCharacterInterface::processNewDirection()
{
    if(nextDirection_ != direction_)
    {
        switch(nextDirection_)
        {
            case Direction::left:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{-1, 0}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::none;
                }
                break;

            case Direction::right:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{+1, 0}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::none;
                }
                break;

            case Direction::up:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{0, -1}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::none;
                }
                break;

            case Direction::down:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{0, +1}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::none;
                }
                break;

            case Direction::none:
                break;
        }
    }
}

void MovableCharacterInterface::validateAndProcessMovement()
{
    switch(direction_)
    {
        case Direction::left:
            if(gameMap_.isPathPointValid(coordinates_ + std::pair{-1, 0}))
            {
                coordinates_ += {-1, 0};
                moving_ = true;
            }
            else
            {
                moving_ = false;
            }
            break;

        case Direction::right:
            if(gameMap_.isPathPointValid(coordinates_ + std::pair{+1, 0}))
            {
                coordinates_ += {+1, 0};
                moving_ = true;
            }
            else
            {
                moving_ = false;
            }
            break;

        case Direction::up:
            if(gameMap_.isPathPointValid(coordinates_ + std::pair{0, -1}))
            {
                coordinates_ += {0, -1};
                moving_ = true;
            }
            else
            {
                moving_ = false;
            }
            break;

        case Direction::down:
            if(gameMap_.isPathPointValid(coordinates_ + std::pair{0, +1}))
            {
                coordinates_ += {0, +1};
                moving_ = true;
            }
            else
            {
                moving_ = false;
            }
            break;

        case Direction::none:
            break;
    }
}

void MovableCharacterInterface::checkAndProcessGameAreaBoundaryReach()
{
    /*Teleportation when reached left boundary of middle horizontal line*/
    if(coordinates_.x_ <= 0)
    {
        coordinates_ = {613, 318};
    }

    /*Teleportation when reached right boundary of middle horizontal line*/
    if(coordinates_.x_ >= 614)
    {
        coordinates_ = {1, 318};
    }
}
