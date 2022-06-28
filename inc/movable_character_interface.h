#pragma once

#include "common.h"
#include "game_map.h"
#include "coordinates.h"

#include <chrono>
#include <memory>

class MovableCharacterInterface
{
public:
    MovableCharacterInterface(const Coordinates& coordinates, Direction initialDirection, const GameMap& gameMap);

    virtual void advanceAnimation() = 0;
    virtual void startMovement() = 0;
    virtual void stopMovement() = 0;
    virtual void reset() = 0;

    [[nodiscard]] const Coordinates& getCoordinates() const {return coordinates_;}
    void setCoordinates(const Coordinates& coordinates){coordinates_ = coordinates;}
    void setNextDirection(Direction direction) {nextDirection_ = direction;}

protected:
    void processNewDirection();
    void validateAndProcessMovement();
    void checkAndProcessGameAreaBoundaryReach();

    const int diameter_ = 30;
    const int offsetX_ = -15;
    const int offsetY_ = -15;

    const std::chrono::milliseconds normalSpeed_ {6};
    const std::chrono::milliseconds reducedSpeed_ {50};

    Coordinates coordinates_;
    int animationState_{};
    bool moving_{};
    Direction direction_;
    Direction nextDirection_;
    const GameMap& gameMap_;
};
