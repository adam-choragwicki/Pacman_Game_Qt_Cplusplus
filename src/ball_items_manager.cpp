#include "ball_items_manager.h"
#include "drawer.h"

BallItemsManager::BallItemsManager()
{

}

BallItemsManager::~BallItemsManager()
{

}

void BallItemsManager::populateMapWithBalls(const GameMap& gameMap)
{
    for(auto& foodballPosition : gameMap.getFoodballPositions())
    {
        foodballGraphicsItems_.push_back(std::make_unique<Foodball>(foodballPosition));
    }

    for(auto& powerballPosition : gameMap.getPowerballPositions())
    {
        powerballGraphicsItems_.push_back(std::make_unique<Powerball>(powerballPosition));
    }
}

void BallItemsManager::removeBalls()
{
    foodballGraphicsItems_.clear();
    powerballGraphicsItems_.clear();
}

bool BallItemsManager::checkAndProcessCollisionWithFoodball(const QGraphicsItem& pacman)
{
    for(auto iter = foodballGraphicsItems_.begin(); iter != foodballGraphicsItems_.end(); ++iter)
    {
        if(pacman.collidesWithItem(iter->get()))
        {
            foodballGraphicsItems_.erase(iter);
            return true;
        }
    }

    return false;
}

bool BallItemsManager::checkAndProcessCollisionWithPowerball(const QGraphicsItem& pacman)
{
    for(auto iter = powerballGraphicsItems_.begin(); iter != powerballGraphicsItems_.end(); ++iter)
    {
        if(pacman.collidesWithItem(iter->get()))
        {
            powerballGraphicsItems_.erase(iter);
            return true;
        }
    }

    return false;
}

uint BallItemsManager::getRemainingFoodballsCount()
{
    return foodballGraphicsItems_.size();
}
