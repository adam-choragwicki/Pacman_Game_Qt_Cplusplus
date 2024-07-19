#pragma once

#include "coordinates.h"
#include <QRect>
#include <QtWidgets/QGraphicsEllipseItem>

class AbstractBall : public QGraphicsEllipseItem
{
public:
    explicit AbstractBall(const Coordinates& coordinates);
    ~AbstractBall() override = 0;

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
