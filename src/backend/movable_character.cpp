#include "movable_character.h"

MovableCharacter::MovableCharacter(const Coordinates& startingCoordinates, const Direction initialDirection, int animationSpeedFactor, int animationPhasesCount) : CustomGraphicsItem(QRectF(0, 0, DIAMETER, DIAMETER)),

                                                                                                                                         STARTING_COORDINATES(startingCoordinates),
                                                                                                                                         STARTING_DIRECTION(initialDirection),
                                                                                                                                         direction_(initialDirection),
                                                                                                                                         nextDirection_(initialDirection),
                                                                                                                                         ANIMATION_SPEED_FACTOR(animationSpeedFactor),
                                                                                                                                         ANIMATION_PHASES_COUNT(animationPhasesCount)
{
    MovableCharacter::reset();
}

MovableCharacter::~MovableCharacter() = default;

void MovableCharacter::reset()
{
    moving_ = false;
    animationPhase_ = 0;
    animationPhaseAscending_ = true;
    stepCounter_ = 0;

    direction_ = STARTING_DIRECTION;
    nextDirection_ = direction_;

    setPos(STARTING_COORDINATES.x_ - static_cast<double>(DIAMETER) / 2, STARTING_COORDINATES.y_ - static_cast<double>(DIAMETER) / 2);
}

void MovableCharacter::moveCharacterBy(const std::pair<int, int>& offset)
{
    moveBy(offset.first, offset.second);
}

void MovableCharacter::moveTo(const Coordinates& coordinates)
{
    setPos(coordinates.x_ - static_cast<double>(DIAMETER) / 2, coordinates.y_ - static_cast<double>(DIAMETER) / 2);
}

void MovableCharacter::advanceAnimation()
{
    ++stepCounter_;

    if(stepCounter_ >= ANIMATION_SPEED_FACTOR)
    {
        stepCounter_ = 0;

        if(animationPhaseAscending_)
        {
            ++animationPhase_;
            if(animationPhase_ == ANIMATION_PHASES_COUNT - 1)
            {
                animationPhaseAscending_ = false;
            }
        }
        else
        {
            --animationPhase_;
            if(animationPhase_ == 0)
            {
                animationPhaseAscending_ = true;
            }
        }
    }
}
