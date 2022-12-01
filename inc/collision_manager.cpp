#include "collision_manager.h"
#include "log_manager.h"

bool CollisionManager::checkAndProcessCollisionWithFoodball(const Coordinates& pacmanCoordinates, std::vector<Foodball>& foodballs)
{
    for(auto& foodball : foodballs)
    {
        if(pacmanCoordinates == foodball.getCoordinates())
        {
            if(foodball.isEaten())
            {
                return false;
            }
            else
            {
                foodball.setEaten(true);
                return true;
            }
        }
    }

    return false;
}

bool CollisionManager::checkAndProcessCollisionWithPowerball(const Coordinates& pacmanCoordinates, std::vector<Powerball>& powerballs)
{
    for(auto& powerball : powerballs)
    {
        if(pacmanCoordinates == powerball.getCoordinates())
        {
            if(powerball.isEaten())
            {
                return false;
            }
            else
            {
                powerball.setEaten(true);
                return true;
            }
        }
    }

    return false;
}

bool CollisionManager::checkCollisionWithGhost(const Coordinates& pacmanCoordinates, const Coordinates& ghostCoordinates)
{
    const int& pacmanX = pacmanCoordinates.x_;
    const int& pacmanY = pacmanCoordinates.y_;

    const int& ghostX = ghostCoordinates.x_;
    const int& ghostY = ghostCoordinates.y_;

    const int COLLISION_DISTANCE = 20;

    return (abs(ghostX - pacmanX) < COLLISION_DISTANCE) && (abs(ghostY - pacmanY) < COLLISION_DISTANCE);
}
