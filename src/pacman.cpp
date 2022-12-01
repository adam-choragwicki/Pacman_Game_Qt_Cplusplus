#include "game_map.h"
#include "pacman.h"

Pacman::Pacman(const GameMap& gameMap) : MovableCharacter(STARTING_COORDINATES, Direction::LEFT, gameMap)
{
    movementTimer_.setInterval(NORMAL_SPEED);
    Pacman::reset();
}

void Pacman::reset()
{
    MovableCharacter::reset();
    direction_ = Direction::LEFT;
    setCoordinates(STARTING_COORDINATES);
}

void Pacman::advanceAnimation()
{
    if(moving_)
    {
        if(animationState_ >= 8 * animationSpeedFactor_)
        {
            animationState_ = 0;
        }
        else
        {
            animationState_++;
        }
    }
}

void Pacman::startMovement()
{
    movementTimer_.start();
}

void Pacman::stopMovement()
{
    movementTimer_.stop();
}

void Pacman::move()
{
    processNewDirection();
    validateAndProcessMovement();
    checkAndProcessGameAreaBoundaryReach();
    advanceAnimation();
}
