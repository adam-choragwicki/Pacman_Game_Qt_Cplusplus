#pragma once

#include "common.h"
#include "game_map.h"
#include "coordinates.h"

class MovableCharacter
{
public:
    MovableCharacter(const Coordinates& coordinates, Direction initialDirection, const GameMap& gameMap);

    virtual void advanceAnimation() = 0;
    virtual void startMovement() = 0;
    virtual void stopMovement() = 0;
    virtual void reset() = 0;

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

    void setCoordinates(const Coordinates& coordinates)
    { coordinates_ = coordinates; }

    void setNextDirection(Direction direction)
    { nextDirection_ = direction; }

    [[nodiscard]] Direction getDirection() const
    {
        return direction_;
    }

    [[nodiscard]] int getAnimationState() const
    {
        return animationState_;
    }

protected:
    void processNewDirection();
    void validateAndProcessMovement();
    void checkAndProcessGameAreaBoundaryReach();

    Coordinates coordinates_;
    int animationState_{};
    bool moving_{};
    Direction direction_;
    Direction nextDirection_;
    const GameMap& gameMap_;
};
