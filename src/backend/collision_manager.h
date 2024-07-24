#pragma once

class QGraphicsItem;
class StandardPellet;
class PowerPellet;

#include <set>

class CollisionManager
{
public:
    static bool checkAndProcessPacmanCollisionWithStandardPellet(const QGraphicsItem& pacman, std::set<StandardPellet>& standardPellets);
    static bool checkAndProcessPacmanCollisionWithPowerPellet(const QGraphicsItem& pacman, std::set<PowerPellet>& powerPellets);
    static bool checkAndProcessPacmanCollisionWithGhost(const QGraphicsItem& pacman, const QGraphicsItem& ghost);
};
