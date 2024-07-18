#pragma once

#include "abstract_ball.h"

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
