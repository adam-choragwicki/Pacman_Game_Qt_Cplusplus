#include "collision_manager.h"
#include "model/balls/foodball.h"
#include "model/balls/powerball.h"
#include "model/ghosts/abstract_ghost.h"

bool CollisionManager::checkAndProcessPacmanCollisionWithFoodball(const QGraphicsItem& pacman, std::set<Foodball>& foodballs)
{
    for(const Foodball& foodball : foodballs)
    {
        if(pacman.collidesWithItem(&foodball))
        {
            foodballs.erase(foodball);
            return true;
        }
    }

    return false;
}

bool CollisionManager::checkAndProcessPacmanCollisionWithPowerball(const QGraphicsItem& pacman, std::set<Powerball>& powerballs)
{
    for(const Powerball& powerball : powerballs)
    {
        if(pacman.collidesWithItem(&powerball))
        {
            powerballs.erase(powerball);
            return true;
        }
    }

    return false;
}

bool CollisionManager::checkAndProcessPacmanCollisionWithGhost(const QGraphicsItem& pacman, const QGraphicsItem& ghost)
{
    return pacman.collidesWithItem(&ghost);
}
