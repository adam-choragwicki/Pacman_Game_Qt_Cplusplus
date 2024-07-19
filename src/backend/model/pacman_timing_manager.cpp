#include "pacman_timing_manager.h"

PacmanTimingManager::PacmanTimingManager()
{
    movementTimer_.setInterval(Config::Timing::MovableCharacter::NORMAL_SPEED);
}

void PacmanTimingManager::startMovement()
{
    movementTimer_.start();
}

void PacmanTimingManager::stopMovement()
{
    movementTimer_.stop();
}
