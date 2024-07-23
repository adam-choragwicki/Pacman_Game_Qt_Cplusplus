#pragma once

class QGraphicsItem;
class Foodball;
class Powerball;

#include <set>

class CollisionManager
{
public:
    static bool checkAndProcessPacmanCollisionWithFoodball(const QGraphicsItem& pacman, std::set<Foodball>& foodballs);
    static bool checkAndProcessPacmanCollisionWithPowerball(const QGraphicsItem& pacman, std::set<Powerball>& powerballs);
    static bool checkAndProcessPacmanCollisionWithGhost(const QGraphicsItem& pacman, const QGraphicsItem& ghost);
};
