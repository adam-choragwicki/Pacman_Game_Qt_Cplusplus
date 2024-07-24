#pragma once

#include "abstract_pellet.h"

class StandardPellet : public AbstractPellet
{
public:
    explicit StandardPellet(const Coordinates& coordinates) : AbstractPellet(coordinates, DIAMETER, OFFSET_X, OFFSET_Y)
    {}

    ~StandardPellet() override = default;

    bool operator<(const StandardPellet& other) const
    {
        return AbstractPellet::operator<(other);
    }

    static const int DIAMETER = 7;

    static const int OFFSET_X = -3;
    static const int OFFSET_Y = -3;
};
