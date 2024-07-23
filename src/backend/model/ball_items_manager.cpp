#include "ball_items_manager.h"
#include "model/balls/foodball.h"
#include "model/balls/powerball.h"
#include "path_points.h"
#include "spdlog/spdlog.h"

BallItemsManager::BallItemsManager(const PathPoints& pathPoints) : pathPoints_(pathPoints)
{}

void BallItemsManager::reset()
{
    spdlog::debug("Reset BallItemsManager");

    foodballs_.clear();
    powerballs_.clear();

    createBalls();
}

void BallItemsManager::createBalls()
{
    spdlog::debug("Creating balls");

    createFoodBalls();
    createPowerballs();
}

size_t BallItemsManager::getRemainingFoodballsCount()
{
    return foodballs_.size();
}

void BallItemsManager::createFoodBalls()
{
    for(const Coordinates& foodballPosition : pathPoints_.getFoodballPositions())
    {
        foodballs_.emplace(foodballPosition);
    }
}

void BallItemsManager::createPowerballs()
{
    for(const Coordinates& powerballPosition : pathPoints_.getPowerballPositions())
    {
        powerballs_.emplace(powerballPosition);
    }
}

void BallItemsManager::hideAllBalls()
{
    std::for_each(foodballs_.begin(), foodballs_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).hide();
    });

    std::for_each(powerballs_.begin(), powerballs_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).hide();
    });
}

void BallItemsManager::showAllBalls()
{
    std::for_each(foodballs_.begin(), foodballs_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).show();
    });

    std::for_each(powerballs_.begin(), powerballs_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).show();
    });
}
