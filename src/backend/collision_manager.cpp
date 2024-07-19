#include "collision_manager.h"
#include "model/balls/foodball.h"
#include "model/balls/powerball.h"

bool CollisionManager::checkAndProcessPacmanCollisionWithFoodball(const QRect& pacmanRect, std::set<Foodball>& foodballs)
{
    for(const Foodball& foodball : foodballs)
    {
        if(pacmanRect.intersects(foodball.getRect()))
        {
            foodballs.erase(foodball);
            return true;
        }
    }

    return false;
}

bool CollisionManager::checkAndProcessPacmanCollisionWithPowerball(const QRect& pacmanRect, std::set<Powerball>& powerballs)
{
    for(const Powerball& powerball : powerballs)
    {
        if(pacmanRect.intersects(powerball.getRect()))
        {
            powerballs.erase(powerball);
            return true;
        }
    }

    return false;
}

bool CollisionManager::checkAndProcessPacmanCollisionWithGhost(const QRect& pacmanRect, const QRect& ghostRect)
{
    return pacmanRect.intersects(ghostRect);
}
