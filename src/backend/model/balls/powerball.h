#pragma once

#include "abstract_ball.h"

class Powerball : public AbstractBall
{
public:
    explicit Powerball(const Coordinates& coordinates) : AbstractBall(coordinates, DIAMETER)
    {}

    ~Powerball() override = default;

    bool operator<(const Powerball& other) const
    {
        return AbstractBall::operator<(other);
    }

    static const int DIAMETER = 15;

    static const int OFFSET_X = -7;
    static const int OFFSET_Y = -7;
};
