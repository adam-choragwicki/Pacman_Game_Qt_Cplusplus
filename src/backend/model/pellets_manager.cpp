#include "pellets_manager.h"
#include "model/pellets/standard_pellet.h"
#include "model/pellets/power_pellet.h"
#include "path_points.h"
#include "spdlog/spdlog.h"

PelletsManager::PelletsManager(const PathPoints& pathPoints) : pathPoints_(pathPoints)
{}

void PelletsManager::reset()
{
    spdlog::debug("Reset PelletsManager");

    standardPellets_.clear();
    powerPellets_.clear();

    createPellets();
}

void PelletsManager::createPellets()
{
    spdlog::debug("Creating pellets");

    createStandardPellets();
    createPowerPellets();
}

size_t PelletsManager::getRemainingStandardPelletsCount()
{
    return standardPellets_.size();
}

void PelletsManager::createStandardPellets()
{
    for(const Coordinates& standardPelletPosition : pathPoints_.getStandardPelletPositions())
    {
        standardPellets_.emplace(standardPelletPosition);
    }
}

void PelletsManager::createPowerPellets()
{
    for(const Coordinates& powerPelletPosition : pathPoints_.getPowerPelletPositions())
    {
        powerPellets_.emplace(powerPelletPosition);
    }
}

void PelletsManager::hideAllPellets()
{
    std::for_each(standardPellets_.begin(), standardPellets_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).hide();
    });

    std::for_each(powerPellets_.begin(), powerPellets_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).hide();
    });
}

void PelletsManager::showAllPellets()
{
    std::for_each(standardPellets_.begin(), standardPellets_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).show();
    });

    std::for_each(powerPellets_.begin(), powerPellets_.end(), [](const QGraphicsItem& item)
    {
        const_cast<QGraphicsItem&>(item).show();
    });
}
