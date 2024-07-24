#include "collision_manager.h"
#include "model/pellets/standard_pellet.h"
#include "model/pellets/power_pellet.h"

bool CollisionManager::checkAndProcessPacmanCollisionWithStandardPellet(const QGraphicsItem& pacman, std::set<StandardPellet>& standardPellets)
{
    for(const StandardPellet& standardPellet : standardPellets)
    {
        if(pacman.collidesWithItem(&standardPellet))
        {
            standardPellets.erase(standardPellet);
            return true;
        }
    }

    return false;
}

bool CollisionManager::checkAndProcessPacmanCollisionWithPowerPellet(const QGraphicsItem& pacman, std::set<PowerPellet>& powerPellets)
{
    for(const PowerPellet& powerPellet : powerPellets)
    {
        if(pacman.collidesWithItem(&powerPellet))
        {
            powerPellets.erase(powerPellet);
            return true;
        }
    }

    return false;
}

bool CollisionManager::checkAndProcessPacmanCollisionWithGhost(const QGraphicsItem& pacman, const QGraphicsItem& ghost)
{
    return pacman.collidesWithItem(&ghost);
}
