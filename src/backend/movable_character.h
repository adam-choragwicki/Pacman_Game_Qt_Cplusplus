#pragma once

#include "common.h"
#include "coordinates.h"
#include "config.h"
#include <QRect>
#include <QObject>
#include <QTimer>
#include <QtWidgets/QGraphicsItem>

class MovableCharacter : public QObject, public QGraphicsItem
{
Q_OBJECT

public:
    MovableCharacter(const Coordinates& startingCoordinates, Direction initialDirection);
    ~MovableCharacter() override = 0;

    virtual void advanceAnimation() = 0;

    virtual void reset();

//    [[nodiscard]] Coordinates getCoordinates() const
//    { return Coordinates{rect_.center().x(), rect_.center().y()}; }

    [[nodiscard]] Coordinates getCoordinates() const
    { return Coordinates{static_cast<int>(sceneBoundingRect().center().x()), static_cast<int>(sceneBoundingRect().center().y())}; }

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

    void moveCharacterBy(const std::pair<int, int>& offset);
    void moveTo(const Coordinates& coordinates);

    [[nodiscard]] QRectF boundingRect() const override
    {
        //        return {static_cast<qreal>(STARTING_COORDINATES.x_ - DIAMETER / 2), static_cast<qreal>(STARTING_COORDINATES.y_ - DIAMETER / 2), static_cast<qreal>(STARTING_COORDINATES.x_ + DIAMETER / 2), static_cast<qreal>(STARTING_COORDINATES.y_ + DIAMETER / 2)};

        return {0, 0, 30, 30};
    }

protected:
    int animationState_{};
    bool moving_{};
    Direction direction_;
    Direction nextDirection_;

    const Coordinates STARTING_COORDINATES;
    const Direction STARTING_DIRECTION;
    QRect rect_;

    QTimer movementTimer_;

private:
    static const int DIAMETER = 30;
};
