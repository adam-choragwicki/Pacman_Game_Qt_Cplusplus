#pragma once

#include "ghost_base.h"

class GhostPurple : public GhostBase
{
public:
    explicit GhostPurple(const GameMap& gameMap);
    ~GhostPurple() override;

    void reset() override;

private:
    QVector<std::string> getImagesUrls();

    inline static const Coordinates startingCoordinates_ {307, 318};
    static constexpr std::chrono::seconds startTimeout_ {1};
};
