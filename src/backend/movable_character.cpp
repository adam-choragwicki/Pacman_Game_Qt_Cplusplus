#include "movable_character.h"

MovableCharacter::MovableCharacter(const Coordinates& startingCoordinates, const Direction initialDirection) :
        STARTING_COORDINATES(startingCoordinates), STARTING_DIRECTION(initialDirection), direction_(initialDirection), nextDirection_(initialDirection)
{
    MovableCharacter::reset();
}

MovableCharacter::~MovableCharacter() = default;

void MovableCharacter::reset()
{
    moving_ = false;
    animationState_ = 0;

    direction_ = STARTING_DIRECTION;
    nextDirection_ = direction_;

    setPos(STARTING_COORDINATES.x_ - DIAMETER / 2, STARTING_COORDINATES.y_ - DIAMETER / 2);
    //    rect_.setCoords(STARTING_COORDINATES.x_ - DIAMETER / 2, STARTING_COORDINATES.y_ - DIAMETER / 2, STARTING_COORDINATES.x_ + DIAMETER / 2, STARTING_COORDINATES.y_ + DIAMETER / 2);
}

void MovableCharacter::moveCharacterBy(const std::pair<int, int>& offset)
{
    moveBy(offset.first, offset.second);
    //    rect_.translate(offset.first, offset.second);
}

void MovableCharacter::moveTo(const Coordinates& coordinates)
{
    setPos(coordinates.x_ - DIAMETER / 2, coordinates.y_ - DIAMETER / 2);
}
