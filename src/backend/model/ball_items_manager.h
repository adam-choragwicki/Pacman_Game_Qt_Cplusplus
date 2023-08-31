#pragma once

#include "ball.h"
#include "path_points.h"
#include "pacman.h"

#include <vector>

class BallItemsManager
{
public:
    explicit BallItemsManager(const PathPoints& pathPoints);
    ~BallItemsManager() = default;

    void createBalls(const PathPoints& pathPoints);

    uint getRemainingFoodballsCount();

    [[nodiscard]] std::set<Foodball>& getFoodballs()
    { return foodballs_; }

    [[nodiscard]] std::set<Powerball>& getPowerballs()
    { return powerballs_; }

private:
    std::set<Foodball> foodballs_;
    std::set<Powerball> powerballs_;
};
