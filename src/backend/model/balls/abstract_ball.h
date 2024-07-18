#pragma once

#include "coordinates.h"
#include <QRect>

class AbstractBall
{
public:
    explicit AbstractBall(const Coordinates& coordinates);
    virtual ~AbstractBall() = 0;

    [[nodiscard]] const Coordinates& getCoordinates() const
    { return coordinates_; }

    [[nodiscard]] QRect getRect() const
    { return rect_; }

    bool operator<(const AbstractBall& other) const;

protected:
    QRect rect_;

private:
    const Coordinates coordinates_;
};
