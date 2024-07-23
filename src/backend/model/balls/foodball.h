#pragma once

#include "abstract_ball.h"

class Foodball : public AbstractBall
{
public:
    explicit Foodball(const Coordinates& coordinates) : AbstractBall(coordinates, DIAMETER, OFFSET_X, OFFSET_Y)
    {}

    ~Foodball() override = default;

    bool operator<(const Foodball& other) const
    {
        return AbstractBall::operator<(other);
    }

    static const int DIAMETER = 7;

    static const int OFFSET_X = -3;
    static const int OFFSET_Y = -3;
};
