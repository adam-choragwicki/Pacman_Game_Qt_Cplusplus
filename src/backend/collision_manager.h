#pragma once

class Foodball;
class Powerball;
class QRect;

#include <set>

class CollisionManager
{
public:
    static bool checkAndProcessCollisionWithFoodball(const QRect& pacmanRect, std::set<Foodball>& foodballs);
    static bool checkAndProcessCollisionWithPowerball(const QRect& pacmanRect, std::set<Powerball>& powerballs);

    static bool checkPacmanCollisionWithAnyGhost(const QRect& pacmanRect, const QRect& ghostRect);


    static bool checkCollisionWithGhost(const QRect& pacmanRect, const QRect& ghostRect);
};
