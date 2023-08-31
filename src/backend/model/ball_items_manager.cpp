#include "model/ball_items_manager.h"

BallItemsManager::BallItemsManager(const PathPoints& pathPoints)
{
    createBalls(pathPoints);
}

void BallItemsManager::createBalls(const PathPoints& pathPoints)
{
    for(auto& foodballPosition : pathPoints.getFoodballPositions())
    {
        foodballs_.emplace(foodballPosition);
    }

    for(auto& powerballPosition : pathPoints.getPowerballPositions())
    {
        powerballs_.emplace(powerballPosition);
    }
}

uint BallItemsManager::getRemainingFoodballsCount()
{
    return foodballs_.size();
}
