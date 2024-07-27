#include "movable_character.h"

MovableCharacter::MovableCharacter(const Coordinates& startingCoordinates, const Direction initialDirection) : CustomGraphicsItem(QRectF(0, 0, DIAMETER, DIAMETER)),

                                                                                                               STARTING_COORDINATES(startingCoordinates),
                                                                                                               STARTING_DIRECTION(initialDirection),
                                                                                                               direction_(initialDirection),
                                                                                                               nextDirection_(initialDirection)
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
