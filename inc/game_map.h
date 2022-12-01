#pragma once

#include "coordinates.h"

#include <set>
#include <array>

class GameMap
{
public:
    GameMap();

    static const int TARGET_FOODBALLS_COUNT = 88;
    static const int TARGET_POWERBALLS_COUNT = 4;

    [[nodiscard]] bool isPathPointValid(const Coordinates& coordinates) const;

    [[nodiscard]] const std::set<Coordinates>& getFoodballPositions() const
    { return FOODBALL_POSITIONS; };

    [[nodiscard]] const std::set<Coordinates>& getPowerballPositions() const
    { return POWERBALL_POSITIONS; };

private:
    const std::set<Coordinates> PATH_POINTS;
    const std::set<Coordinates> POWERBALL_POSITIONS;
    const std::set<Coordinates> FOODBALL_POSITIONS;

    std::set<Coordinates> generatePathPointsBetweenPoints(int startX, int startY, int endX, int endY);
    std::set<Coordinates> generatePathPoints();
    std::set<Coordinates> generateFoodballPositions();
    std::set<Coordinates> generatePowerballPositions();
};
