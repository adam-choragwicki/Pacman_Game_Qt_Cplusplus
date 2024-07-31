#pragma once

#include <QRect>
#include <QObject>
#include <QTimer>
#include "common.h"
#include "coordinates.h"
#include "custom_graphics_item.h"

class MovableCharacter : public QObject, public CustomGraphicsItem
{
Q_OBJECT

public:
    MovableCharacter(const Coordinates& startingCoordinates, Direction initialDirection, int animationSpeedFactor, int animationPhasesCount);
    ~MovableCharacter() override = 0;

    void advanceAnimation();

    virtual void reset();

    [[nodiscard]] Coordinates getCoordinates() const
    { return Coordinates{static_cast<int>(sceneBoundingRect().center().x()), static_cast<int>(sceneBoundingRect().center().y())}; }

    void setNextDirection(Direction direction)
    { nextDirection_ = direction; }

    [[nodiscard]] Direction getDirection() const
    { return direction_; }

    [[nodiscard]] Direction getNextDirection() const
    { return nextDirection_; }

    [[nodiscard]] bool isMoving() const
    { return moving_; }

    void setDirection(Direction direction)
    { direction_ = direction; }

    void setMoving(bool moving)
    { moving_ = moving; }

    void moveCharacterBy(const std::pair<int, int>& offset);
    void moveTo(const Coordinates& coordinates);

protected:
    bool moving_{};
    Direction direction_;
    Direction nextDirection_;

    const Coordinates STARTING_COORDINATES;
    const Direction STARTING_DIRECTION;

    const int ANIMATION_SPEED_FACTOR;
    const int ANIMATION_PHASES_COUNT;

    int animationPhase_{};
    bool animationPhaseAscending_ = true;
    int stepCounter_{};

private:
    static const int DIAMETER = 30;
};
