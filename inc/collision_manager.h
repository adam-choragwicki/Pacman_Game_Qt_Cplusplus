#pragma once

#include "ball.h"
#include "ghosts/abstract_ghost.h"

#include <vector>

class CollisionManager
{
public:
    static bool checkAndProcessCollisionWithFoodball(const Coordinates& pacmanCoordinates, std::vector<Foodball>& foodballs);
    static bool checkAndProcessCollisionWithPowerball(const Coordinates& pacmanCoordinates, std::vector<Powerball>& powerballs);
    static bool checkCollisionWithGhost(const Coordinates& pacmanCoordinates, const Coordinates& ghostCoordinates);
};
