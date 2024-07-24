#pragma once

#include "abstract_pellet.h"

class PowerPellet : public AbstractPellet
{
public:
    explicit PowerPellet(const Coordinates& coordinates) : AbstractPellet(coordinates, DIAMETER, OFFSET_X, OFFSET_Y)
    {}

    ~PowerPellet() override = default;

    bool operator<(const PowerPellet& other) const
    {
        return AbstractPellet::operator<(other);
    }

    static const int DIAMETER = 15;

    static const int OFFSET_X = -7;
    static const int OFFSET_Y = -7;
};
