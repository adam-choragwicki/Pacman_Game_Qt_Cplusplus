#pragma once

#include "coordinates.h"
#include <set>

class PathPoints
{
public:
    PathPoints();

    static const int TARGET_STANDARD_PELLETS_COUNT = 88;
    static const int TARGET_POWER_PELLETS_COUNT = 4;

    [[nodiscard]] bool isPathPointValid(const Coordinates& coordinates) const;

    [[nodiscard]] const std::set<Coordinates>& getStandardPelletPositions() const
    { return STANDARD_PELLETS_POSITIONS; };

    [[nodiscard]] const std::set<Coordinates>& getPowerPelletPositions() const
    { return POWER_PELLETS_POSITIONS; };

private:
    const std::set<Coordinates> PATH_POINTS;
    const std::set<Coordinates> POWER_PELLETS_POSITIONS;
    const std::set<Coordinates> STANDARD_PELLETS_POSITIONS;

    std::set<Coordinates> generatePathPointsBetweenPoints(int startX, int startY, int endX, int endY);
    std::set<Coordinates> generatePathPoints();
    std::set<Coordinates> generateStandardPelletsPositions();
    std::set<Coordinates> generatePowerPelletsPositions();
};
