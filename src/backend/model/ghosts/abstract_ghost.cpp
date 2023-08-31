#include "model/ghosts/abstract_ghost.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection) : MovableCharacter(coordinates, initialDirection)
{
    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::reset()
{
    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
}

bool AbstractGhost::isScared() const
{
    return (scaredState_ == ScaredState::SCARED_BLUE) || (scaredState_ == ScaredState::SCARED_WHITE);
}

bool AbstractGhost::isScaredWhite() const
{
    return scaredState_ == ScaredState::SCARED_WHITE;
}

bool AbstractGhost::isScaredBlue() const
{
    return scaredState_ == ScaredState::SCARED_BLUE;
}

void AbstractGhost::advanceAnimation()
{
    if(animationState_ > 2)
    {
        setAnimationState(0);
    }
    else
    {
        ++animationState_;
    }
}
