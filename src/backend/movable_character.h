#pragma once

#include "common.h"
#include "coordinates.h"
#include "config.h"
#include <QRect>

class MovableCharacter
{
public:
    MovableCharacter(const Coordinates& startingCoordinates, Direction initialDirection);
    virtual ~MovableCharacter() = 0;

    virtual void advanceAnimation() = 0;

    virtual void reset();

    [[nodiscard]] Coordinates getCoordinates() const
    { return Coordinates{rect_.center().x(), rect_.center().y()}; }

    void setNextDirection(Direction direction)
    { nextDirection_ = direction; }

    [[nodiscard]] Direction getDirection() const
    { return direction_; }

    [[nodiscard]] Direction getNextDirection() const
    { return nextDirection_; }

    [[nodiscard]] int getAnimationState() const
    { return animationState_; }

    void setAnimationState(int animationState)
    { animationState_ = animationState; }

    [[nodiscard]] QRect getRect() const
    { return rect_; }

    [[nodiscard]] bool isMoving() const
    { return moving_; }

    void setDirection(Direction direction)
    { direction_ = direction; }

    void setMoving(bool moving)
    { moving_ = moving; }

    void moveBy(const std::pair<int, int>& offset);
    void moveTo(const Coordinates& coordinates);

protected:
    int animationState_{};
    bool moving_{};
    Direction direction_;
    Direction nextDirection_;

    const Coordinates STARTING_COORDINATES;
    const Direction STARTING_DIRECTION;
    QRect rect_;

private:
    static const int DIAMETER = 30;
};
