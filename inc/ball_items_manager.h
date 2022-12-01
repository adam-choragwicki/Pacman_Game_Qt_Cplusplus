#pragma once

#include "ball.h"
#include "game_map.h"
#include "pacman.h"

#include <vector>
#include <memory>

class BallItemsManager
{
public:
    explicit BallItemsManager(const GameMap& gameMap);
    ~BallItemsManager() = default;

    void createBalls(const GameMap& gameMap);
    void resetBalls();

    uint getRemainingFoodballsCount();

    [[nodiscard]] std::vector<Foodball>& getFoodballs()
    { return foodballs_; }

    [[nodiscard]] std::vector<Powerball>& getPowerballs()
    { return powerballs_; }

private:
    std::vector<Foodball> foodballs_;
    std::vector<Powerball> powerballs_;
};
