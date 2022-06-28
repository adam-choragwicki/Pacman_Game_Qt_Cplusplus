#pragma once

#include "ghost_base.h"

class GhostRed : public GhostBase
{
public:
    explicit GhostRed(const GameMap& gameMap);
    ~GhostRed() override;

    void reset() override;

private:
    QVector<std::string> getImagesUrls();

    inline static const Coordinates startingCoordinates_ {307, 252};
    inline static const Coordinates coordinatesAfterRespawn_ {307, 318};
    static constexpr std::chrono::seconds startTimeout_{0};
};
