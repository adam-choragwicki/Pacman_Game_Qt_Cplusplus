#include "ball_items_manager.h"
#include "model/balls/foodball.h"
#include "model/balls/powerball.h"

#include "path_points.h"


BallItemsManager::BallItemsManager(const PathPoints& pathPoints)
{
    createBalls(pathPoints);
}

void BallItemsManager::createBalls(const PathPoints& pathPoints)
{
    for(const Coordinates& foodballPosition : pathPoints.getFoodballPositions())
    {
        foodballs_.emplace(foodballPosition);
    }

    for(const Coordinates& powerballPosition : pathPoints.getPowerballPositions())
    {
        powerballs_.emplace(powerballPosition);
    }
}

size_t BallItemsManager::getRemainingFoodballsCount()
{
    return foodballs_.size();
}
