#include "ball_items_manager.h"

BallItemsManager::BallItemsManager(const GameMap& gameMap)
{
    createBalls(gameMap);
}

void BallItemsManager::createBalls(const GameMap& gameMap)
{
    for(auto& foodballPosition : gameMap.getFoodballPositions())
    {
        foodballs_.emplace_back(foodballPosition);
    }

    for(auto& powerballPosition : gameMap.getPowerballPositions())
    {
        powerballs_.emplace_back(powerballPosition);
    }
}

void BallItemsManager::resetBalls()
{
    for(auto& foodball : foodballs_)
    {
        foodball.setEaten(false);
    }

    for(auto& powerball : powerballs_)
    {
        powerball.setEaten(false);
    }
}

uint BallItemsManager::getRemainingFoodballsCount()
{
    auto isNotEaten = [](const Foodball& foodball)
    {
        return !foodball.isEaten();
    };

    return std::ranges::count_if(foodballs_, isNotEaten);
}
