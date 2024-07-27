#pragma once

#include <QRect>
#include <QObject>
#include <QTimer>
#include "common.h"
#include "coordinates.h"
#include "config.h"
#include "custom_graphics_item.h"

class MovableCharacter : public QObject, public CustomGraphicsItem
{
Q_OBJECT

public:
    MovableCharacter(const Coordinates& startingCoordinates, Direction initialDirection);
    ~MovableCharacter() override = 0;

    virtual void advanceAnimation() = 0;

    virtual void reset();

    [[nodiscard]] Coordinates getCoordinates() const
    { return Coordinates{static_cast<int>(sceneBoundingRect().center().x()), static_cast<int>(sceneBoundingRect().center().y())}; }

    void setNextDirection(Direction direction)
    { nextDirection_ = direction; }

    [[nodiscard]] Direction getDirection() const
    { return direction_; }

    [[nodiscard]] Direction getNextDirection() const
    { return nextDirection_; }

    void setAnimationPhase(int animationPhase)
    { animationPhase_ = animationPhase; }

    [[nodiscard]] bool isMoving() const
    { return moving_; }

    void setDirection(Direction direction)
    { direction_ = direction; }

    void setMoving(bool moving)
    { moving_ = moving; }

    void moveCharacterBy(const std::pair<int, int>& offset);
    void moveTo(const Coordinates& coordinates);

protected:
    int animationPhase_{};
    bool moving_{};
    Direction direction_;
    Direction nextDirection_;

    const Coordinates STARTING_COORDINATES;
    const Direction STARTING_DIRECTION;

private:
    static const int DIAMETER = 30;
};
