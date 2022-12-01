#include "movable_character.h"

MovableCharacter::MovableCharacter(const Coordinates& coordinates, Direction initialDirection, const GameMap& gameMap) :
        coordinates_(coordinates), direction_(initialDirection), gameMap_(gameMap)
{
    nextDirection_ = Direction::NONE;
    MovableCharacter::reset();
}

void MovableCharacter::reset()
{
    moving_ = false;
    nextDirection_ = Direction::NONE;
    animationState_ = 0;
}

void MovableCharacter::processNewDirection()
{
    if(nextDirection_ != direction_)
    {
        switch(nextDirection_)
        {
            case Direction::LEFT:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{-1, 0}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::NONE;
                }
                break;

            case Direction::RIGHT:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{+1, 0}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::NONE;
                }
                break;

            case Direction::UP:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{0, -1}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::NONE;
                }
                break;

            case Direction::DOWN:
                if(gameMap_.isPathPointValid(coordinates_ + std::pair{0, +1}))
                {
                    direction_ = nextDirection_;
                    nextDirection_ = Direction::NONE;
                }
                break;

            case Direction::NONE:
                break;
        }
    }
}

void MovableCharacter::validateAndProcessMovement()
{
    switch(direction_)
    {
        case Direction::LEFT:
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

        case Direction::RIGHT:
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

        case Direction::UP:
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

        case Direction::DOWN:
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

        case Direction::NONE:
            break;
    }
}

void MovableCharacter::checkAndProcessGameAreaBoundaryReach()
{
    /*Teleportation when reached LEFT boundary of middle horizontal line*/
    if(coordinates_.x_ <= 0)
    {
        coordinates_ = {613, 318};
    }

    /*Teleportation when reached RIGHT boundary of middle horizontal line*/
    if(coordinates_.x_ >= 614)
    {
        coordinates_ = {1, 318};
    }
}
