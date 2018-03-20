#pragma once

#include <cstddef>
#include <set>

class StandardPellet;
class PowerPellet;
class PathPoints;

class PelletsManager
{
public:
    explicit PelletsManager(const PathPoints& pathPoints);
    ~PelletsManager() = default;

    void reset();

    size_t getRemainingStandardPelletsCount();

    [[nodiscard]] std::set<StandardPellet>& getStandardPellets()
    { return standardPellets_; }

    [[nodiscard]] std::set<PowerPellet>& getPowerPellets()
    { return powerPellets_; }

    void hideAllPellets();
    void showAllPellets();

private:
    void createPellets();
    void createStandardPellets();
    void createPowerPellets();

    const PathPoints& pathPoints_;

    std::set<StandardPellet> standardPellets_;
    std::set<PowerPellet> powerPellets_;
};
