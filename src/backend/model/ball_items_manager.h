#pragma once

#include <cstddef>
#include <set>

class Foodball;
class Powerball;
class PathPoints;

class BallItemsManager
{
public:
    explicit BallItemsManager(const PathPoints& pathPoints);
    ~BallItemsManager() = default;

    void createBalls(const PathPoints& pathPoints);

    size_t getRemainingFoodballsCount();

    [[nodiscard]] std::set<Foodball>& getFoodballs()
    { return foodballs_; }

    [[nodiscard]] std::set<Powerball>& getPowerballs()
    { return powerballs_; }

private:
    std::set<Foodball> foodballs_;
    std::set<Powerball> powerballs_;
};
