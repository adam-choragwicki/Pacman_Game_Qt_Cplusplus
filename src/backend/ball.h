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

class Foodball : public AbstractBall
{
public:
    explicit Foodball(const Coordinates& coordinates);
    ~Foodball() override = default;

    bool operator<(const Foodball& other) const
    {
        return AbstractBall::operator<(other);
    }
};

class Powerball : public AbstractBall
{
public:
    explicit Powerball(const Coordinates& coordinates);
    ~Powerball() override = default;

    bool operator<(const Powerball& other) const
    {
        return AbstractBall::operator<(other);
    }
};
