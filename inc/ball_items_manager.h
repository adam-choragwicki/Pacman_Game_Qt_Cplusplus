#pragma once

#include "ball.h"
#include "game_map.h"

class BallItemsManager
{
public:
    BallItemsManager();
    ~BallItemsManager();

    void populateMapWithBalls(const GameMap& gameMap);
    void removeBalls();
    bool checkAndProcessCollisionWithFoodball(const QGraphicsItem& pacman);
    bool checkAndProcessCollisionWithPowerball(const QGraphicsItem& pacman);
    uint getRemainingFoodballsCount();

private:
    std::vector<std::unique_ptr<Foodball>> foodballGraphicsItems_;
    std::vector<std::unique_ptr<Powerball>> powerballGraphicsItems_;
};
