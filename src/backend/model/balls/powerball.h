#pragma once

#include "abstract_ball.h"

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
