#include "model/pacman.h"

Pacman::Pacman() : MovableCharacter(Config::StartingCoordinates::PACMAN, Config::InitialDirection::PACMAN)
{}

void Pacman::advanceAnimation()
{
    if(animationState_ >= 8 * Config::Timing::Pacman::ANIMATION_SPEED_FACTOR)
    {
        animationState_ = 0;
    }
    else
    {
        ++animationState_;
    }
}
